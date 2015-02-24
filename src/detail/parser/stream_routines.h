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

#ifndef PELI_DETAIL_PARSER_STREAM_ROUTINES_H
#define PELI_DETAIL_PARSER_STREAM_ROUTINES_H

#include <istream>
#include <string>

namespace peli
{
	namespace detail
	{
		namespace parser
		{
			template<typename Ch> void skip_whitespace(std::basic_istream<Ch>& is);

			template<> void skip_whitespace<char>(std::istream& is);
			template<> void skip_whitespace<wchar_t>(std::wistream& is);

			template<typename Ch> std::basic_string<Ch> get_value(std::basic_istream<Ch>& is);

			template<> std::string get_value<char>(std::istream& is);
			template<> std::wstring get_value<wchar_t>(std::wistream& is);
		}
	}
}

#endif // PELI_DETAIL_PARSER_STREAM_ROUTINES_H
