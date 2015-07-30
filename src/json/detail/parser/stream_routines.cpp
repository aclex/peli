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

#include "json/detail/special_chars.h"

using namespace std;

using namespace peli::json::detail;
using namespace peli::json::detail::parser;

namespace
{
	template<typename Ch> inline void skip_whitespace_generic(basic_streambuf<Ch>* rdbuf)
	{
		typename std::basic_streambuf<Ch>::int_type c = rdbuf->sgetc();
		while(is_whitespace(c))
		{
			c = rdbuf->snextc();
		}
	}
}

template<> void peli::json::detail::parser::skip_whitespace<char>(basic_streambuf<char>* rdbuf)
{
	skip_whitespace_generic(rdbuf);
}

template<> void peli::json::detail::parser::skip_whitespace<wchar_t>(basic_streambuf<wchar_t>* rdbuf)
{
	skip_whitespace_generic(rdbuf);
}
