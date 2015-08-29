/*
 * This file is part of Peli - universal JSON interaction library
 * Copyright (C) 2014  Alexey Chernov <4ernov@gmail.com>
 *
 * Peli is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "peli/json/value.h"

#include "json/detail/parser/tokenizer.h"
#include "json/detail/printer/typewriter.h"

#include "peli/detail/template_snippets/templated_visitor.h"
#include "peli/detail/template_snippets/bind_specialization.h"

using namespace peli::json;
using namespace peli::detail;
using namespace peli::detail::template_snippets;

namespace
{
	template<typename BaseVisitor, typename Typewriter, typename Arg> struct object_atomic_typewriter_visitor : virtual public BaseVisitor
	{
		void visit(const Arg& v) override
		{
			static_cast<Typewriter*>(this)->print(v);
		}
	};

	template<typename BaseVisitor, typename Typewriter, typename Arg> struct value_atomic_typewriter_visitor : virtual public BaseVisitor
	{
		void visit(Arg v) override
		{
			static_cast<Typewriter*>(this)->print(v);
		}
	};

	template<typename BaseVisitor, typename Typewriter, typename Arg> using atomic_typewriter_visitor =
		typename std::conditional<std::is_fundamental<Arg>::value,
			value_atomic_typewriter_visitor<BaseVisitor, Typewriter, Arg>, object_atomic_typewriter_visitor<BaseVisitor, Typewriter, Arg>>::type;

	template<typename UpstreamVisitor, typename DownstreamVisitor, typename... Ts> using typewriter_visitor =
		templated_visitor::using_unfolder<bind_specialization<atomic_typewriter_visitor, UpstreamVisitor, DownstreamVisitor>::template type, Ts...>;

	template<typename Ch, typename VariantVisitor, typename ConcreteVisitor> struct printing_visitor_template :
		detail::printer::typewriter<Ch, ConcreteVisitor>,
		VariantVisitor::template refine<bind_specialization<typewriter_visitor, VariantVisitor, ConcreteVisitor>::template type>::type
	{
		using detail::printer::typewriter<Ch, ConcreteVisitor>::typewriter;
		void visit() override { this->print(); }
	};
}

std::istream& peli::json::operator>>(std::istream& is, value& v)
{
	v = peli::json::detail::parser::tokenizer::gentle_stream(is);
	return is;
}

std::wistream& peli::json::operator>>(std::wistream& is, value& v)
{
	v = peli::json::detail::parser::tokenizer::gentle_stream(is);
	return is;
}

std::ostream& peli::json::operator<<(std::ostream& os, const value& v)
{
	typedef value::variant_type::visitor variant_visitor;
	struct printing_visitor : public printing_visitor_template<char, variant_visitor, printing_visitor>
	{
		using printing_visitor_template<char, variant_visitor, printing_visitor>::printing_visitor_template;
		void visit(const peli::json::value& v)
		{
			v.m_variant.accept(this);
		}
	};

	printing_visitor visitor(os);

	v.m_variant.accept(&visitor);
	return os;
}

std::wostream& peli::json::operator<<(std::wostream& os, const value& v)
{
	typedef value::variant_type::visitor variant_visitor;
	struct printing_visitor : public printing_visitor_template<wchar_t, variant_visitor, printing_visitor>
	{
		using printing_visitor_template<wchar_t, variant_visitor, printing_visitor>::printing_visitor_template;
		void visit(const peli::json::value& v)
		{
			v.m_variant.accept(this);
		}
	};

	printing_visitor visitor(os);

	v.m_variant.accept(&visitor);
	return os;
}

