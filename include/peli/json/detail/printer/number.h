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

#ifndef PELI_DETAIL_PRINTER_NUMBER_H
#define PELI_DETAIL_PRINTER_NUMBER_H

#include <ostream>
#include <limits>

#include "peli/json/number.h"

#include "peli/json/detail/printer/stream_routines.h"

#include <floaxie/ftoa.h>

namespace peli
{
	namespace json
	{
		namespace detail
		{
			namespace printer
			{
				/** \brief `head` specialization for [JSON](https://json.org) number.
				 * \see `head`
				 */
				template<> struct head<json::number>
				{
				public:
					template<class Visitor> static void print(Visitor& v, const json::number n)
					{
						put_structure_space(v);

						typename Visitor::char_type buf[floaxie::max_buffer_size<double>()];
						const auto written_size { floaxie::ftoa(static_cast<double>(n), buf) };

						v.putn(buf, written_size);
					}
				};
			}
		}
	}
}

#endif // PELI_DETAIL_PRINTER_NUMBER_H
