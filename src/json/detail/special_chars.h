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

#ifndef PELI_DETAIL_PARSER_SPECIAL_CHARS_H
#define PELI_DETAIL_PARSER_SPECIAL_CHARS_H

namespace peli
{
	namespace json
	{
		namespace detail
		{
			namespace special_chars
			{
				constexpr const char backspace = 0x08; // '\b'
				constexpr const char tab = 0x09; // '\t'
				constexpr const char lf = 0x0a; // '\n'
				constexpr const char ff = 0x0c; // '\f'
				constexpr const char cr = 0x0d; // '\r'
				constexpr const char space = 0x20; // ' '

				constexpr const char comma = 0x2c; // ','
				constexpr const char quote = 0x22; // '"'
				constexpr const char colon = 0x3a; // ':'
				constexpr const char left_curly = 0x7b; // '{'
				constexpr const char right_curly = 0x7d; // '}'
				constexpr const char left_square = 0x5b; // '['
				constexpr const char right_square = 0x5d; // ']'

				constexpr const char slash = 0x2f; // '/'
				constexpr const char backslash = 0x5c; // '\'

				constexpr const char a = 0x61; // 'a'
				constexpr const char b = 0x62; // 'b'
				constexpr const char e = 0x65; // 'e'
				constexpr const char f = 0x66; // 'f'
				constexpr const char n = 0x6e; // 'n'
				constexpr const char l = 0x6c; // 'l'
				constexpr const char r = 0x72; // 'r'
				constexpr const char s = 0x73; // 's'
				constexpr const char t = 0x74; // 't'
				constexpr const char u = 0x75; // 'u'

				constexpr const char d0 = 0x30; // '0'
			}
		}
	}
}

#endif // PELI_DETAIL_PARSER_SPECIAL_CHARS_H
