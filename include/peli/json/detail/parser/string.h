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
#include <tuple>
#include <array>
#include <cstdint>

#include "peli/except.h"

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
				/** \brief `parser` specialization for [JSON](https://json.org) string.
				 * \see `parser`
				 */
				template<typename Ch> class parser<std::basic_string<Ch>>
				{
				public:
					template<class InputBuffer> static std::basic_string<typename InputBuffer::char_type> parse(InputBuffer& buf)
					{
						using char_type = typename InputBuffer::char_type;

						std::basic_string<char_type> ret;

						stream_string(buf, ret);

						return ret;
					}

				private:
					template<class InputBuffer> static inline void stream_string(InputBuffer& buf, std::basic_string<typename InputBuffer::char_type>& ret)
					{
						auto c { buf.getc() };

						if (c != special_chars::quote)
							throw parse_error("No starting quotation mark found while parsing a string.");

						c = buf.nextc();

						while(c != InputBuffer::eof())
						{
							switch (c)
							{
							case special_chars::quote:
								buf.bumpc();
								return;

							case special_chars::backslash:
								buf.bumpc();
								stream_char(buf, ret);
								c = buf.getc();
								break;

							default:
								ret += c;
								c = buf.nextc();
								break;
							}
						}

						throw parse_error("No ending quotation mark found while parsing a string.");
					}

					template<class InputBuffer> static inline void stream_char(InputBuffer& buf, std::basic_string<typename InputBuffer::char_type>& ret)
					{
						auto c { buf.getc() };

						switch (c)
						{
						case special_chars::quote:
						case special_chars::backslash:
						case special_chars::slash:
							buf.bumpc();
							ret += c;
							break;

						case special_chars::b:
							buf.bumpc();
							ret += 0x08;
							break;

						case special_chars::f:
							buf.bumpc();
							ret += 0x0c;
							break;

						case special_chars::n:
							buf.bumpc();
							ret += 0x0a;
							break;

						case special_chars::r:
							buf.bumpc();
							ret += 0x0d;
							break;

						case special_chars::t:
							buf.bumpc();
							ret += 0x09;
							break;

						case special_chars::u:
							buf.bumpc();
							stream_unicode_sequence(buf, ret);
							break;

						default:
							throw parse_error("Invalid escape sequence found.");
						}
					}

					template<class InputBuffer> static void stream_unicode_sequence(InputBuffer& buf, std::basic_string<typename InputBuffer::char_type>& ret)
					{
						const auto cp { extract_codepoint(buf) };

						if (utf::is_lead_surrogate(cp))
						{
							auto c { buf.getc() };

							if (c != special_chars::backslash)
								throw parse_error("Incorrect surrogate pair found.");

							c = buf.nextc();

							if (c != special_chars::u)
								throw parse_error("Incorrect surrogate pair found.");

							buf.bumpc();

							const auto trail_cp { extract_codepoint(buf) };
							ret += utf::convert<Ch>(cp, trail_cp);
						}
						else
						{
							ret += utf::convert<Ch>(cp);
						}
					}

					template<class InputBuffer> static inline std::uint_fast16_t extract_codepoint(InputBuffer& buf)
					{
						auto ret { static_cast<std::uint_fast16_t>(s_ch_to_hex[buf.bumpc()] << 12) };
						ret += s_ch_to_hex[buf.bumpc()] << 8;
						ret += s_ch_to_hex[buf.bumpc()] << 4;
						ret += s_ch_to_hex[buf.bumpc()];

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
