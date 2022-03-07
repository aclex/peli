/*
 * This file is part of Peli - universal JSON interaction library
 * Copyright (C) 2014-2022  Alexey Chernov <4ernov@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
