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

#ifndef PELI_DETAIL_PRINTER_STRING_H
#define PELI_DETAIL_PRINTER_STRING_H

#include <array>
#include <string>

#include "peli/json/detail/special_chars.h"

namespace peli
{
	namespace json
	{
		namespace detail
		{
			namespace printer
			{
				/** \brief `head` specialization for [JSON](https://json.org) string.
				 * \see `head`
				 */
				template<typename Ch> class head<std::basic_string<Ch>>
				{
				public:
					template<class Visitor> static void print(Visitor& v, const std::basic_string<typename Visitor::char_type>& str)
					{
						using namespace special_chars;

						put_structure_space(v);

						v.putc(quote);

						for (Ch cs : str)
							stream_char(v, cs);

						v.putc(quote);
					}

				private:
					template<class Visitor> static void stream_char(Visitor& v, const typename Visitor::char_type c)
					{
						using namespace special_chars;

						switch (c)
						{
						// special characters
						case quote:
						case backslash:
							v.putc(backslash);
							v.putc(c);
							break;

						// control characters with predefined verbal escape sequences
						case backspace:
							v.putc(backslash);
							v.putc(b);
							break;

						case tab:
							v.putc(backslash);
							v.putc(t);
							break;

						case lf:
							v.putc(backslash);
							v.putc(n);
							break;

						case ff:
							v.putc(backslash);
							v.putc(f);
							break;

						case cr:
							v.putc(backslash);
							v.putc(r);
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
							v.putc(backslash);
							v.putc(u);
							auto pnt = hex(c);
							v.putn(pnt.data(), pnt.size());
							break;
						}

						// normal characters
						default:
							v.putc(c);
							break;
						}
					}

					static std::array<Ch, 4> hex(Ch c)
					{
						static constexpr std::size_t sz(4);

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
