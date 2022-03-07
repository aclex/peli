/*
 * This file is part of Peli - universal JSON interaction library
 * Copyright (C) 2014-2022  Alexey Chernov <4ernov@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef PELI_DETAIL_PARSER_SPECIAL_CHARS_H
#define PELI_DETAIL_PARSER_SPECIAL_CHARS_H

namespace peli
{
	namespace json
	{
		/** \brief Implementation detail of [JSON](https://json.org) part */
		namespace detail
		{
			/** \brief Constants for some often used characters. */
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

				constexpr const char minus = 0x2d; // '-'

				constexpr const char d0 = 0x30; // '0'
				constexpr const char d1 = 0x31; // '1'
				constexpr const char d2 = 0x32; // '2'
				constexpr const char d3 = 0x33; // '3'
				constexpr const char d4 = 0x34; // '4'
				constexpr const char d5 = 0x35; // '5'
				constexpr const char d6 = 0x36; // '6'
				constexpr const char d7 = 0x37; // '7'
				constexpr const char d8 = 0x38; // '8'
				constexpr const char d9 = 0x39; // '9'
			}
		}
	}
}

#endif // PELI_DETAIL_PARSER_SPECIAL_CHARS_H
