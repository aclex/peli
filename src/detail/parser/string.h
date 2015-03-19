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

#include "peli/json/array.h"

#include "detail/special_chars.h"

#include "detail/parser/parser.h"
#include "detail/parser/stream_routines.h"
#include "detail/parser/utf.h"

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

					stream_string(is, ret);

					ret.shrink_to_fit();

					return ret;
				}

			private:
				static inline void stream_string(std::basic_istream<Ch>& is, std::basic_string<Ch>& ret)
				{
					Ch c = is.get();
					if (c != special_chars::quote)
					{
						is.unget();
						throw std::invalid_argument("");
					}

					c = is.get();
					while(true)
					{
						switch (c)
						{
						case special_chars::quote:
							return;

						case special_chars::backslash:
							stream_char(is, ret);
							break;

						default:
							ret += c;
							break;
						}

						c = is.get();
					}
				}
				static inline void stream_char(std::basic_istream<Ch>& is, std::basic_string<Ch>& ret)
				{
					Ch c = is.get();
					switch (c)
					{
					case special_chars::quote:
					case special_chars::backslash:
					case special_chars::slash:
						ret += c;
						break;

					case special_chars::b:
						ret += 0x08;
						break;

					case special_chars::f:
						ret += 0x0c;
						break;

					case special_chars::n:
						ret += 0x0a;
						break;

					case special_chars::r:
						ret += 0x0d;
						break;

					case special_chars::t:
						ret += 0x09;
						break;

					case special_chars::u:
						stream_unicode_sequence(is, ret);
						break;

					default:
						throw std::invalid_argument("");
					}
				}

				static void stream_unicode_sequence(std::basic_istream<Ch>& is, std::basic_string<Ch>& ret)
				{
					auto cp = extract_codepoint(is);

					if (utf::is_lead_surrogate(cp))
					{
						if (!(is.get() == special_chars::backslash && is.get() == special_chars::u))
							throw std::invalid_argument("");

						auto trail_cp = extract_codepoint(is);
						ret += utf::convert<Ch>(cp, trail_cp);
					}
					else
					{
						ret += utf::convert<Ch>(cp);
					}
				}

				static inline std::uint_fast16_t extract_codepoint(std::basic_istream<Ch>& is)
				{
					std::uint_fast16_t ret = s_ch_to_hex[is.get()] << 12;
					ret += s_ch_to_hex[is.get()] << 8;
					ret += s_ch_to_hex[is.get()] << 4;
					ret += s_ch_to_hex[is.get()];

					return ret;
				}

				static constexpr std::size_t s_reserved_size = 256;

				static constexpr std::array<char, special_chars::f + 1> s_ch_to_hex
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

			template<typename Ch> constexpr std::array<char, special_chars::f + 1> parser<std::basic_string<Ch>>::s_ch_to_hex;
		}
	}
}

#endif // PELI_DETAIL_PARSER_STRING_H
