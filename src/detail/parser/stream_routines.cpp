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

#include "stream_routines.h"

#include "detail/special_chars.h"

using namespace std;

using namespace peli::detail;
using namespace peli::detail::parser;

namespace
{
	template<typename Ch> bool is_whitespace(Ch c)
	{
		switch (c)
		{
		case special_chars::tab:
		case special_chars::lf:
		case special_chars::cr:
		case special_chars::space:
			return true;

		default:
			return false;
		}
	}

	template<typename Ch> bool is_value_delimiter(Ch c)
	{
		if (is_whitespace(c))
			return true;

		switch (c)
		{
		case special_chars::comma:
		case special_chars::right_curly:
		case special_chars::right_square:
			return true;

		default:
			return false;
		}
	}

	template<typename Ch> void skip_whitespace_generic(basic_istream<Ch>& is)
	{
		while(is_whitespace(is.peek()))
			is.get();
	}

	template<typename Ch> void get_value_generic(basic_istream<Ch>& is, basic_string<Ch>& buf)
	{
		buf.clear();

		while(!is_value_delimiter(is.peek()))
		{
			buf += is.get();
		}
	}
}

template<> void peli::detail::parser::skip_whitespace<char>(istream& is)
{
	skip_whitespace_generic(is);
}

template<> void peli::detail::parser::skip_whitespace<wchar_t>(wistream& is)
{
	skip_whitespace_generic(is);
}

template<> void peli::detail::parser::get_value<char>(istream& is, string& buf)
{
	get_value_generic(is, buf);
}

template<> void peli::detail::parser::get_value<wchar_t>(wistream& is, wstring& buf)
{
	get_value_generic(is, buf);
}
