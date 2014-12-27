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

#include "parser.h"

using namespace std;

using namespace peli::detail::parser;

namespace
{
	template<typename Ch> bool is_whitespace(Ch c)
	{
		switch (c)
		{
		case 0x09:
		case 0x0a:
		case 0x0d:
		case 0x20:
			return true;

		default:
			return false;
		}
	}

	template<typename Ch> void skip_whitespace_generic(std::basic_istream<Ch>& is)
	{
		while(is_whitespace(is.peek()))
			is.get();
	}
}

void peli::detail::parser::skip_whitespace(istream& is)
{
	skip_whitespace_generic(is);
}

void peli::detail::parser::skip_whitespace(wistream& is)
{
	skip_whitespace_generic(is);
}
