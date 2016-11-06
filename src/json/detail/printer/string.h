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

#ifndef PELI_DETAIL_PRINTER_STRING_H
#define PELI_DETAIL_PRINTER_STRING_H

#include <array>
#include <ostream>
#include <string>
#include <iomanip>
#include <type_traits>

#include "json/detail/printer/head.h"

#include "json/detail/special_chars.h"

namespace peli
{
	namespace json
	{
		namespace detail
		{
			namespace printer
			{
				template<typename Ch> class head<std::basic_string<Ch>>
				{
				public:
					template<typename Typewriter,
					typename std::enable_if<std::is_same<typename Typewriter::char_type, Ch>::value, int>::type c = 0>
					static void print(Typewriter* tw, const std::basic_string<Ch>& str)
					{
						using namespace special_chars;

						tw->rdbuf->sputc(quote);

						for (Ch cs : str)
							stream_char(tw, cs);

						tw->rdbuf->sputc(quote);
					}

					template<typename Typewriter,
					typename std::enable_if<!std::is_same<typename Typewriter::char_type, Ch>::value, int>::type c = 0>
					static void print(Typewriter*, const std::basic_string<Ch>&)
					{
						throw std::invalid_argument("Incompatible character types.");
					}

				private:
					template<typename Typewriter> static void stream_char(Typewriter* tw, Ch c)
					{
						using namespace special_chars;

						switch (c)
						{
						// special characters
						case quote:
						case backslash:
						case slash:
							tw->rdbuf->sputc(backslash);
							tw->rdbuf->sputc(c);
							break;

						// control characters with predefined verbal escape sequences
						case backspace:
							tw->rdbuf->sputc(backslash);
							tw->rdbuf->sputc(b);
							break;

						case tab:
							tw->rdbuf->sputc(backslash);
							tw->rdbuf->sputc(t);
							break;

						case lf:
							tw->rdbuf->sputc(backslash);
							tw->rdbuf->sputc(n);
							break;

						case ff:
							tw->rdbuf->sputc(backslash);
							tw->rdbuf->sputc(f);
							break;

						case cr:
							tw->rdbuf->sputc(backslash);
							tw->rdbuf->sputc(r);
							break;

						// other control characters of the range 0x00...0x1F
						case 0x00:
						case 0x01:
						case 0x02:
						case 0x03:
						case 0x04:
						case 0x05:
						case 0x06:
						case 0x07:
						case 0x0b:
						case 0x0e:
						case 0x0f:
						case 0x10:
						case 0x11:
						case 0x12:
						case 0x13:
						case 0x14:
						case 0x15:
						case 0x16:
						case 0x17:
						case 0x18:
						case 0x19:
						case 0x1a:
						case 0x1b:
						case 0x1c:
						case 0x1d:
						case 0x1e:
						case 0x1f:
						{
							tw->rdbuf->sputc(backslash);
							tw->rdbuf->sputc(u);
							auto pnt = hex(c);
							tw->rdbuf->sputn(&pnt.front(), pnt.size());
							break;
						}

						// normal characters
						default:
							tw->rdbuf->sputc(c);
							break;
						}
					}

					static std::array<Ch, 4> hex(Ch c)
					{
						constexpr std::size_t sz(4);

						static char hex [] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' ,'a', 'b', 'c', 'd', 'e', 'f' };

						std::array<Ch, sz> ret;

						for (size_t resd = 1; resd <= sz; ++resd)
						{
							ret[sz - resd] = hex[c & 0xf];
							c >>= 4;
						}

						return ret;
					}
				};
			}
		}
	}
}

#endif // PELI_DETAIL_PRINTER_STRING_H
