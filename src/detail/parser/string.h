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
#include <array>
#include <cstdint>

#include <peli/json/array.h>

#include "detail/parser/parser.h"
#include "detail/parser/utf.h"
#include "detail/parser/special_chars.h"

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

					if (is.peek() != special_chars::quote)
						throw std::invalid_argument("");

					is.get();

					std::basic_string<Ch> buf;
					buf.reserve(s_reserved_size);

					while (true)
					{
						std::getline(is, buf, static_cast<Ch>(special_chars::quote));

						ret += buf;

						if (buf.back() != special_chars::backslash)
							break;

						ret += special_chars::quote;
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
					case special_chars::quote:
					case special_chars::backslash:
					case special_chars::slash:
						break;

					case special_chars::b:
						str[pos + 1] = 0x08;
						break;

					case special_chars::f:
						str[pos + 1] = 0x0c;
						break;

					case special_chars::n:
						str[pos + 1] = 0x0a;
						break;

					case special_chars::r:
						str[pos + 1] = 0x0d;
						break;

					case special_chars::t:
						str[pos + 1] = 0x09;
						break;

					case special_chars::u:
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
					typename std::basic_string<Ch>::size_type encoding_pos = pos + 2;
					auto cp = extract_codepoint(str, encoding_pos);

					if (utf::is_lead_surrogate(cp))
					{
						encoding_pos += 6;
						auto trail_cp = extract_codepoint(str, encoding_pos);

						const auto& sst = utf::convert<Ch>(cp, trail_cp);
						auto replace_pos = pos + 12 - sst.length();

						str.replace(replace_pos, sst.length(), sst);

						return std::make_pair(sst.length(), replace_pos - pos);
					}

					const auto& sst = utf::convert<Ch>(cp);
					auto replace_pos = pos + 6 - sst.length();

					str.replace(replace_pos, sst.length(), sst);

					return std::make_pair(sst.length(), replace_pos - pos);
				}

				static constexpr std::uint_fast16_t extract_codepoint(std::basic_string<Ch>& str, typename std::basic_string<Ch>::size_type& encoding_pos)
				{
					return (s_ch_to_hex[str[encoding_pos + 0]] << 12) +
							(s_ch_to_hex[str[encoding_pos + 1]] << 8) +
							(s_ch_to_hex[str[encoding_pos + 2]] << 4) +
							 s_ch_to_hex[str[encoding_pos + 3]];
				}

				static constexpr std::size_t s_reserved_size = 4096;


				static constexpr std::array<unsigned int, special_chars::f + 1> s_ch_to_hex
				{{
					0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0, 0, 0, 0, 0, 0,
					0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0, 0, 0, 0, 0, 0,
					0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0, 0, 0, 0, 0, 0,
					0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0, 0, 0, 0, 0, 0,
					0, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, 0x0, 0x0, 0x0, 0, 0, 0, 0, 0, 0,
					0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0, 0, 0, 0, 0, 0,
					0, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf
				}};
			};

			template<typename Ch> constexpr std::array<unsigned int, special_chars::f + 1> parser<std::basic_string<Ch>>::s_ch_to_hex;
		}
	}
}

#endif // PELI_DETAIL_PARSER_STRING_H
