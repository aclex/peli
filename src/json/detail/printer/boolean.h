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

#ifndef PELI_DETAIL_PRINTER_BOOLEAN_H
#define PELI_DETAIL_PRINTER_BOOLEAN_H

#include <array>
#include <ostream>

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
				template<> struct head<bool> : pretty_head<head, bool>, simple_formatter
				{
				public:
					template<typename Typewriter> static void bounce(Typewriter* tw, bool b)
					{
						using namespace special_chars;

						static std::array<typename Typewriter::char_type, 4> true_str { t, r, u, e };
						static std::array<typename Typewriter::char_type, 5> false_str { f, a, l, s, e };

						if (b)
							put(tw->rdbuf, true_str);
						else
							put(tw->rdbuf, false_str);
					}

				private:
					template<typename Ch, std::size_t N> static void put(std::basic_streambuf<Ch>* rdbuf, const std::array<Ch, N>& str)
					{
						rdbuf->sputn(&str.front(), str.size());
					}
				};
			}
		}
	}
}

#endif // PELI_DETAIL_PRINTER_BOOLEAN_H
