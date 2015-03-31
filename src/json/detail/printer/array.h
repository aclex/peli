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
					template<typename Ch> static void bounce(std::basic_ostream<Ch>& os, const peli::json::array& arr)
					{
						const bool we_are_pretty = os.iword(flag_storage_index()) & flag::pretty;

						long& tab_level = os.iword(tab_level_storage_index());

						using namespace special_chars;

						if (we_are_pretty)
						{
							for (long i = 0; i < tab_level; ++i)
								os << "\t";
						}

						os << left_square;

						if (we_are_pretty && !arr.empty())
						{
							os << std::endl;
						}

						++tab_level;

						for (auto it = arr.cbegin(); it != arr.cend(); ++it)
						{
							os << (*it);
							if (it != --arr.cend())
								os << comma;

							if (we_are_pretty)
							{
								os << std::endl;
							}
						}

						--tab_level;

						if (we_are_pretty)
						{
							for (long i = 0; i < tab_level; ++i)
								os << "\t";
						}

						os << right_square;
					}
				};
			}
		}
	}
}

#endif // PELI_DETAIL_PRINTER_ARRAY_H
