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

#ifndef PELI_DETAIL_PRINTER_UTIL_H
#define PELI_DETAIL_PRINTER_UTIL_H

#include <ios>

namespace peli
{
	namespace json
	{
		namespace detail
		{
			namespace printer
			{
				inline int flag_storage_index()
				{
					static int i { std::ios_base::xalloc() };
					return i;
				}

				inline int tab_level_storage_index()
				{
					static int i { std::ios_base::xalloc() };
					return i;
				}

				namespace flag
				{
					const long pretty = 0x01;
					const long structure_newline = 0x02;

					constexpr bool get(const long& flag_word, long flag) { return flag_word & flag; }
					inline void set(long& flag_word, long flag) { flag_word |= flag; }
					inline void unset(long& flag_word, long flag) { flag_word &= ~flag; }
				}
			}
		}
	}
}

#endif // PELI_DETAIL_PRINTER_UTIL_H