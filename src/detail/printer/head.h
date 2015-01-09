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

#ifndef PELI_DETAIL_PRINTER_HEAD_H
#define PELI_DETAIL_PRINTER_HEAD_H

#include <ostream>

namespace peli
{
	namespace detail
	{
		namespace printer
		{
			template<typename Ch, typename T> class head
			{
			public:
				static void print(std::basic_ostream<Ch>& os, const T& v);
			};
		}
	}
}

#endif // PELI_DETAIL_PRINTER_HEAD_H