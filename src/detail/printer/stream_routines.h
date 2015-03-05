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

#ifndef PELI_DETAIL_PRINTER_STREAM_ROUTINES_H
#define PELI_DETAIL_PRINTER_STREAM_ROUTINES_H

#include <ostream>

#include <iostream>

#include "detail/printer/util.h"
#include "detail/special_chars.h"

namespace peli
{
	namespace detail
	{
		namespace printer
		{
			template<typename Ch> bool should_process(std::basic_ostream<Ch>& os)
			{
				const long& flag_word = os.iword(flag_storage_index());
				const bool we_are_pretty = flag::get(flag_word, flag::pretty);
				const bool need_structure_newline = flag::get(flag_word, flag::structure_newline);

				return we_are_pretty && need_structure_newline;
			}

			template<typename Ch> void put_tab_spacing(std::basic_ostream<Ch>& os)
			{
				const long& flag_word = os.iword(flag_storage_index());
				const bool we_are_pretty = flag::get(flag_word, flag::pretty);
				const long& tab_level = os.iword(tab_level_storage_index());

				if (we_are_pretty)
				{
					for (long i = 0; i < tab_level; ++i)
						os << "\t";
				}
			}

			template<typename Ch> void put_structure_newline(std::basic_ostream<Ch>& os)
			{
				if (should_process(os))
					os << std::endl;
			}

			template<typename Ch> void put_structure_space(std::basic_ostream<Ch>& os)
			{
				if (should_process(os))
					os << special_chars::space;
				else
					put_tab_spacing(os);
			}
		}
	}
}

#endif // PELI_DETAIL_PRINTER_STREAM_ROUTINES_H
