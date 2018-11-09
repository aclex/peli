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

#include "peli/json/detail/parser/tokenizer.h"
#include "peli/json/detail/printer/visitor.h"

using namespace peli::json;

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
	peli::json::detail::printer::visitor<typename std::ostream::char_type> print_visitor(os);

#ifdef INTERNAL_VARIANT
	namespace ns = peli::detail::variant;
#else
	namespace ns = std;
#endif

	ns::visit(print_visitor, v.m_variant);

	return os;
}

std::wostream& peli::json::operator<<(std::wostream& os, const value& v)
{
	peli::json::detail::printer::visitor<typename std::wostream::char_type> print_visitor(os);

#ifdef INTERNAL_VARIANT
	namespace ns = peli::detail::variant;
#else
	namespace ns = std;
#endif

	ns::visit(print_visitor, v.m_variant);

	return os;
}
