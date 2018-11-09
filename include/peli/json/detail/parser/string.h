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

#include "peli/json/detail/special_chars.h"

#include "peli/json/detail/parser/parser.h"
#include "peli/json/detail/parser/stream_routines.h"
#include "peli/json/detail/parser/utf.h"

namespace peli
{
	namespace json
	{
		namespace detail
		{
			namespace parser
			{
				template<typename Ch> class parser<std::basic_string<Ch>>
				{
				public:
					static typename std::basic_string<Ch> parse(std::basic_streambuf<Ch>* rdbuf)
					{
						std::basic_string<Ch> ret;

						stream_string(rdbuf, ret);

						return ret;
					}

				private:
					static inline void stream_string(std::basic_streambuf<Ch>* rdbuf, std::basic_string<Ch>& ret)
					{
						typename std::basic_streambuf<Ch>::int_type c = rdbuf->sgetc();

						if (c != special_chars::quote)
							throw std::invalid_argument("No starting quote found while parsing a string");

						c = rdbuf->snextc();

						while(c != std::basic_streambuf<Ch>::traits_type::eof())
						{
							switch (c)
							{
							case special_chars::quote:
								rdbuf->sbumpc();
								return;

							case special_chars::backslash:
								rdbuf->sbumpc();
								stream_char(rdbuf, ret);
								c = rdbuf->sgetc();
								break;

							default:
								ret += c;
								c = rdbuf->snextc();
								break;
							}
						}

						throw std::invalid_argument("No ending quote found while parsing a string");
					}

					static inline void stream_char(std::basic_streambuf<Ch>* rdbuf, std::basic_string<Ch>& ret)
					{
						typename std::basic_streambuf<Ch>::int_type c = rdbuf->sgetc();

						switch (c)
						{
						case special_chars::quote:
						case special_chars::backslash:
						case special_chars::slash:
							rdbuf->sbumpc();
							ret += c;
							break;

						case special_chars::b:
							rdbuf->sbumpc();
							ret += 0x08;
							break;

						case special_chars::f:
							rdbuf->sbumpc();
							ret += 0x0c;
							break;

						case special_chars::n:
							rdbuf->sbumpc();
							ret += 0x0a;
							break;

						case special_chars::r:
							rdbuf->sbumpc();
							ret += 0x0d;
							break;

						case special_chars::t:
							rdbuf->sbumpc();
							ret += 0x09;
							break;

						case special_chars::u:
							rdbuf->sbumpc();
							stream_unicode_sequence(rdbuf, ret);
							break;

						default:
							throw std::invalid_argument("Invalid escape sequence");
						}
					}

					static void stream_unicode_sequence(std::basic_streambuf<Ch>* rdbuf, std::basic_string<Ch>& ret)
					{
						auto cp = extract_codepoint(rdbuf);

						if (utf::is_lead_surrogate(cp))
						{
							typename std::basic_streambuf<Ch>::int_type c = rdbuf->sgetc();

							if (c != special_chars::backslash)
								throw std::invalid_argument("Incorrect surrogate pair");

							c = rdbuf->snextc();

							if (c != special_chars::u)
								throw std::invalid_argument("Incorrect surrogate pair");

							rdbuf->sbumpc();

							auto trail_cp = extract_codepoint(rdbuf);
							ret += utf::convert<Ch>(cp, trail_cp);
						}
						else
						{
							ret += utf::convert<Ch>(cp);
						}
					}

					static inline std::uint_fast16_t extract_codepoint(std::basic_streambuf<Ch>* rdbuf)
					{
						std::uint_fast16_t ret = s_ch_to_hex[rdbuf->sbumpc()] << 12;
						ret += s_ch_to_hex[rdbuf->sbumpc()] << 8;
						ret += s_ch_to_hex[rdbuf->sbumpc()] << 4;
						ret += s_ch_to_hex[rdbuf->sbumpc()];

						return ret;
					}

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
}

#endif // PELI_DETAIL_PARSER_STRING_H
