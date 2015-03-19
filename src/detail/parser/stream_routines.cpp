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
	template<typename Ch> inline void skip_whitespace_generic(basic_istream<Ch>& is)
	{
		while(is_whitespace(is.get()));

		is.unget();
	}

	template<typename Ch> inline void get_number_value_generic(basic_istream<Ch>& is, basic_string<Ch>& buf)
	{
		Ch c = is.get();
		while(!is_value_delimiter(c))
		{
			buf += c;
			c = is.get();
		}

		is.unget();
	}

	template<typename Ch> inline void get_string_generic(basic_istream<Ch>& is, basic_string<Ch>& buf)
	{
		Ch c = is.get();
		Ch prev_c = 0;
		while(!(c == special_chars::quote && prev_c != special_chars::backslash))
		{
			buf += c;
			prev_c = c;
			c = is.get();
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

template<> void peli::detail::parser::get_number_value<char>(istream& is, string& buf)
{
	get_number_value_generic(is, buf);
}

template<> void peli::detail::parser::get_number_value<wchar_t>(wistream& is, wstring& buf)
{
	get_number_value_generic(is, buf);
}

template<> void peli::detail::parser::get_string<char>(istream& is, string& buf)
{
	get_string_generic(is, buf);
}

template<> void peli::detail::parser::get_string<wchar_t>(wistream& is, wstring& buf)
{
	get_string_generic(is, buf);
}
