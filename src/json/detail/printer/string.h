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

#include <ostream>
#include <string>
#include <iomanip>

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
					static void print(std::basic_ostream<Ch>& os, const std::basic_string<Ch>& str)
					{
						using namespace special_chars;

						os << quote;

						for (Ch c : str)
							stream_char(os, c);

						os << quote;
					}

				private:
					static void stream_char(std::basic_ostream<Ch>& os, Ch c)
					{
						using namespace special_chars;

						switch (c)
						{
						// special characters
						case quote:
						case backslash:
						case slash:
							os << backslash << c;
							break;

						// control characters with predefined verbal escape sequences
						case backspace:
							os << backslash << b;
							break;

						case tab:
							os << backslash << t;
							break;

						case lf:
							os << backslash << n;
							break;

						case ff:
							os << backslash << f;
							break;

						case cr:
							os << backslash << r;
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
							os << backslash << u << std::setw(4) << std::setfill(Ch(d0)) << std::hex << int(c);
							break;

						// normal characters
						default:
							os << c;
							break;
						}
					}
				};
			}
		}
	}
}

#endif // PELI_DETAIL_PRINTER_STRING_H
