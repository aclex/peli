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
#include <ios>

#include "json/detail/printer/util.h"
#include "json/detail/special_chars.h"

namespace peli
{
	namespace json
	{
		namespace detail
		{
			namespace printer
			{
				template<typename Ch> inline bool is_pretty_printing(std::basic_ostream<Ch>& os)
				{
					return flag::get(os.iword(flag_storage_index()), flag::pretty);
				}

				template<typename Ch> inline bool needs_structure_newline(std::basic_ostream<Ch>& os)
				{
					return flag::get(os.iword(flag_storage_index()), flag::structure_newline);
				}

				template<typename Ch> inline void set_needs_structure_newline(std::basic_ostream<Ch>& os, bool value)
				{
					value ? flag::set(os.iword(flag_storage_index()), flag::structure_newline) :
						flag::unset(os.iword(flag_storage_index()), flag::structure_newline);
				}

				template<typename Ch> inline long& tab_level(std::basic_ostream<Ch>& os)
				{
					return os.iword(tab_level_storage_index());
				}

				template<typename Ch> inline bool should_process(std::basic_ostream<Ch>& os)
				{
					return is_pretty_printing(os) && needs_structure_newline(os);
				}

				template<typename Ch> inline void put_space(std::basic_ostream<Ch>& os)
				{
					if (is_pretty_printing(os))
						os.rdbuf()->sputc(special_chars::space);
				}

				template<typename Ch> inline void put_tab_spacing(std::basic_ostream<Ch>& os)
				{
					if (is_pretty_printing(os))
					{
						const size_t tl = tab_level(os);
						for (size_t i = 0; i < tl; ++i)
							os.rdbuf()->sputc(special_chars::tab);
					}
				}

				template<typename Ch> inline void put_newline(std::basic_ostream<Ch>& os)
				{
					if (is_pretty_printing(os))
						os.rdbuf()->sputc(special_chars::lf);
				}

				template<typename Ch> inline void put_structure_newline(std::basic_ostream<Ch>& os)
				{
					if (needs_structure_newline(os))
					{
						put_newline(os);
					}
				}

				template<typename Ch> inline void put_structure_space(std::basic_ostream<Ch>& os)
				{
					if (should_process(os))
						os.rdbuf()->sputc(special_chars::space);
					else
						put_tab_spacing(os);
				}
			}
		}
	}
}

#endif // PELI_DETAIL_PRINTER_STREAM_ROUTINES_H
