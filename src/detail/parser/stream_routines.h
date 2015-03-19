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

#include "detail/special_chars.h"

namespace peli
{
	namespace detail
	{
		namespace parser
		{
				template<typename Ch> inline bool is_whitespace(Ch c)
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

				template<typename Ch> inline bool is_value_delimiter(Ch c)
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

			template<typename Ch> void skip_whitespace(std::basic_istream<Ch>& is);

			template<> void skip_whitespace<char>(std::istream& is);
			template<> void skip_whitespace<wchar_t>(std::wistream& is);

			template<typename Ch> void get_number_value(std::basic_istream<Ch>& is, std::basic_string<Ch>& buf);

			template<> void get_number_value<char>(std::istream& is, std::string& buf);
			template<> void get_number_value<wchar_t>(std::wistream& is, std::wstring& buf);

			template<typename Ch> void get_string(std::basic_istream<Ch>& is, std::basic_string<Ch>& buf);

			template<> void get_string<char>(std::istream& is, std::string& buf);
			template<> void get_string<wchar_t>(std::wistream& is, std::wstring& buf);
		}
	}
}

#endif // PELI_DETAIL_PARSER_STREAM_ROUTINES_H