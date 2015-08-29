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
				template<typename Typewriter> inline bool should_process(Typewriter* t)
				{
					return t->pretty && t->need_structure_newline;
				}

				template<typename Typewriter> inline void put_space(Typewriter* t)
				{
					if (t->pretty)
						t->rdbuf->sputc(special_chars::space);
				}

				template<typename Typewriter> inline void put_tab_spacing(Typewriter* t)
				{
					if (t->pretty)
					{
						for (size_t i = 0; i < t->tab_level; ++i)
							t->rdbuf->sputc(special_chars::tab);
					}
				}

				template<typename Typewriter> inline void put_structure_newline(Typewriter* t)
				{
					if (should_process(t))
					{
						put_newline(t);
					}
				}

				template<typename Typewriter> inline void put_newline(Typewriter* t)
				{
					if (t->pretty)
						t->rdbuf->sputc(special_chars::lf);
				}

				template<typename Typewriter> inline void put_structure_space(Typewriter* t)
				{
					if (should_process(t))
						t->rdbuf->sputc(special_chars::space);
					else
						put_tab_spacing(t);
				}

				template<typename Ch> inline bool is_pretty_printing(std::basic_ostream<Ch>& os)
				{
					return flag::get(os.iword(flag_storage_index()), flag::pretty);
				}

				template<typename Typewriter> inline void set_structure_newline(Typewriter* t, bool value)
				{
					if (t->pretty)
						t->need_structure_newline = value;
				}
			}
		}
	}
}

#endif // PELI_DETAIL_PRINTER_STREAM_ROUTINES_H
