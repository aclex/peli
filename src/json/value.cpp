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
#include "peli/json/parser.h"
#include "peli/json/printer.h"

using namespace peli::json;

namespace
{
	template<typename Ch> std::basic_istream<Ch>& generic_stream_in(std::basic_istream<Ch>& is, value& v)
	{
		v = parser::parse(is);
		return is;
	}

	template<typename Ch> std::basic_ostream<Ch>& generic_stream_out(std::basic_ostream<Ch>& os, const value& v)
	{
		printer::print(os, v);
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
	return generic_stream_out(os, v);
}

std::wostream& peli::json::operator<<(std::wostream& os, const value& v)
{
	return generic_stream_out(os, v);
}

