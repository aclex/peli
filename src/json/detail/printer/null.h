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

#ifndef PELI_DETAIL_PRINTER_NULL_H
#define PELI_DETAIL_PRINTER_NULL_H

#include <array>

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
				template<> struct head<void> : pretty_head<head, void>, simple_formatter
				{
				public:
					template<typename Typewriter> static void bounce(Typewriter* t)
					{
						using namespace special_chars;

						static std::array<typename Typewriter::char_type, 4> null_str { n, u, l, l };

						t->rdbuf->sputn(&null_str.front(), null_str.size());
					}
				};
			}
		}
	}
}

#endif // PELI_DETAIL_PRINTER_NULL_H
