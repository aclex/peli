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

#ifndef PELI_DETAIL_PRINTER_ARRAY_H
#define PELI_DETAIL_PRINTER_ARRAY_H

#include <ostream>

#include "peli/json/array.h"
#include "peli/json/value.h"
#include "peli/json/iomanip.h"

#include "json/detail/printer/head.h"
#include "json/detail/printer/util.h"
#include "json/detail/printer/stream_routines.h"

#include "json/detail/special_chars.h"

namespace peli
{
	namespace json
	{
		namespace detail
		{
			namespace printer
			{
				template<> struct head<json::array> : pretty_head<head, json::array>, object_formatter
				{
					template<typename Typewriter> static void bounce(Typewriter* tw, const peli::json::array& arr)
					{
						using namespace special_chars;

						put_tab_spacing(tw);

						tw->rdbuf->sputc(left_square);

						if (!arr.empty())
						{
							put_newline(tw);
						}

						++(tw->tab_level);

						for (auto it = arr.cbegin(); it != arr.cend(); ++it)
						{
							tw->print(*it);

							if (it != --arr.cend())
								tw->rdbuf->sputc(comma);

							put_newline(tw);
						}

						--(tw->tab_level);

						put_tab_spacing(tw);

						tw->rdbuf->sputc(right_square);
					}
				};
			}
		}
	}
}

#endif // PELI_DETAIL_PRINTER_ARRAY_H
