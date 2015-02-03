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

#ifndef PELI_DETAIL_PARSER_STRING_H
#define PELI_DETAIL_PARSER_STRING_H

#include <string>
#include <stdexcept>
#include <tuple>

#include <peli/json/array.h>

#include "detail/parser/parser.h"

namespace peli
{
	namespace detail
	{
		namespace parser
		{
			template<typename Ch> class parser<std::basic_string<Ch>>
			{
			public:
				static typename std::basic_string<Ch> parse(std::basic_istream<Ch>& is)
				{
					std::basic_string<Ch> ret;
					ret.reserve(s_reserved_size);

					if (is.peek() != s_quote)
						throw std::invalid_argument("");

					is.get();

					std::basic_string<Ch> buf;
					buf.reserve(s_reserved_size);

					while (true)
					{
						std::getline(is, buf, s_quote);

						ret += buf;

						if (buf.back() != s_backslash)
							break;

						ret += s_quote;
					}

					process_escapes(ret);

					ret.shrink_to_fit();

					return ret;
				}

			private:
				static void process_escapes(std::basic_string<Ch>& str)
				{
					typename std::basic_string<Ch>::size_type search_start = 0;

					while (search_start < str.length())
					{
						search_start = parse_escape(str, str.find('\\', search_start));


					}
				}

				static typename std::basic_string<Ch>::size_type parse_escape(std::basic_string<Ch>& str, typename std::basic_string<Ch>::size_type pos)
				{
					if (pos >= str.length())
						return pos;

					typename std::basic_string<Ch>::size_type ptr_pos = pos + 1;
					Ch ptr_ch = str[ptr_pos];

					typename std::basic_string<Ch>::difference_type erase_npos = 1;
					typename std::basic_string<Ch>::difference_type shift_npos = 1;


					switch (ptr_ch)
					{
					case s_quote:
					case s_backslash:
					case s_slash: // slash
						break;

					case 0x62: // b
						str[pos + 1] = 0x08;
						break;

					case 0x66:
						str[pos + 1] = 0x0c;
						break;

					case 0x6e:
						str[pos + 1] = 0x0a;
						break;

					case 0x72:
						str[pos + 1] = 0x0d;
						break;

					case 0x74:
						str[pos + 1] = 0x09;
						break;

					case 0x75:
						std::tie(shift_npos, erase_npos) = parse_unicode_chain(str, pos);
						break;

					default:
						break;
					}

					str.erase(pos, erase_npos);

					return pos + shift_npos;
				}

				static std::tuple<typename std::basic_string<Ch>::size_type, typename std::basic_string<Ch>::size_type>
				parse_unicode_chain(std::basic_string<Ch>& str, typename std::basic_string<Ch>::size_type& pos)
				{
					typename std::basic_string<Ch>::size_type encoding_pos = pos + 1;

				}

				static const std::size_t s_reserved_size = 4096;
				static const Ch s_quote = 0x22; // '"'
				static const Ch s_slash = 0x2f; // '/'
				static const Ch s_backslash = 0x5c; // '\'
			};
		}
	}
}

#endif // PELI_DETAIL_PARSER_STRING_H
