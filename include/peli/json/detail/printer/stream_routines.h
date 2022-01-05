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

#include "peli/json/detail/printer/util.h"
#include "peli/json/detail/special_chars.h"

namespace peli
{
	namespace json
	{
		namespace detail
		{
			namespace printer
			{
				/** \brief Puts space, if pretty-printing. */
				template<class Visitor> inline void put_space(Visitor& v)
				{
					if (v.pretty())
						v.putc(special_chars::space);
				}

				/** \brief Puts tab indentation, if pretty-printing. */
				template<class Visitor> inline void put_tab_spacing(Visitor& v)
				{
					if (v.pretty())
					{
						const size_t tl = v.tab_level();
						for (size_t i = 0; i < tl; ++i)
							v.putc(special_chars::tab);
					}
				}

				/** \brief Puts tab new line, if pretty-printing. */
				template<class Visitor> inline void put_newline(Visitor& v)
				{
					if (v.pretty())
						v.putc(special_chars::lf);
				}

				/** \brief Puts tab new line, if local document structure context
				 * requires and if pretty-printing.
				 *
				 */
				template<class Visitor> inline void put_structure_newline(Visitor& v)
				{
					if (v.need_structure_period())
					{
						put_newline(v);
						put_tab_spacing(v);
						v.set_need_structure_period(false);
					}
				}

				/** \brief Puts space, if local document structure context
				 * requires and if pretty-printing.
				 *
				 */
				template<class Visitor> inline void put_structure_space(Visitor& v)
				{
					if (v.need_structure_period())
					{
						put_space(v);
					}
				}
			}
		}
	}
}

#endif // PELI_DETAIL_PRINTER_STREAM_ROUTINES_H
