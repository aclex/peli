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
#include "json/detail/printer/printer.h"

using namespace peli::json;

namespace
{
	template<typename Ch> std::basic_istream<Ch>& generic_stream_in(std::basic_istream<Ch>& is, value& v)
	{
		v = peli::json::detail::parser::tokenizer::gentle_stream(is);
		return is;
	}

	template<typename Derived> class printing_dispatcher
	{
	protected:
		template<class> struct fake_dependency : std::false_type { };

		template<typename T> void dispatch(const T& v)
		{
			static_cast<Derived*>(this)->print(v);
		}

		void dispatch()
		{
			static_cast<Derived*>(this)->print();
		}
	};

	template<class Visitor, typename Ch> class printing_visitor_template :
			public Visitor,
			public peli::json::detail::printer::basic_printer<Ch>,
			public printing_dispatcher<printing_visitor_template<Visitor, Ch>>
	{
	public:
		using peli::json::detail::printer::basic_printer<Ch>::basic_printer;

		void visit(const peli::json::object& v) override { this->template dispatch(v); }
		void visit(const peli::json::wobject& v) override { this->template dispatch(v); }
		void visit(const peli::json::array& v) override { this->template dispatch(v); }
		void visit(const std::string& v) override { this->template dispatch(v); }
		void visit(const std::wstring& v) override { this->template dispatch(v); }
		void visit(peli::json::number v) override { this->template dispatch(v); }
		void visit(bool v) override { this->template dispatch(v); }
		void visit() { this->dispatch(); }
	};

	template<typename Visitor, typename Ch> printing_visitor_template<Visitor, Ch> printing_visitor(std::basic_ostream<Ch>& os)
	{
		return printing_visitor_template<Visitor, Ch>(os);
	}

	template<typename Visitor, typename Variant, typename Ch>
	std::basic_ostream<Ch>& generic_stream_out(std::basic_ostream<Ch>& os, const Variant& v)
	{
		auto visitor(printing_visitor<Visitor>(os));

		if (v.valid())
			v.accept(&visitor);
		else
			visitor.visit();

		return os;
	}
}

std::istream& peli::json::operator>>(std::istream& is, value& v)
{
	return generic_stream_in(is, v);
}

std::wistream& peli::json::operator>>(std::wistream& is, value& v)
{
	return generic_stream_in(is, v);
}

std::ostream& peli::json::operator<<(std::ostream& os, const value& v)
{
	return generic_stream_out<value::variant_type::visitor>(os, v.m_variant);
}

std::wostream& peli::json::operator<<(std::wostream& os, const value& v)
{
	return generic_stream_out<value::variant_type::visitor>(os, v.m_variant);
}

