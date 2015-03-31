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
				template<typename T> class head
				{
					template<class> struct fake_dependency : public std::false_type { };

				public:
					template<typename Ch> static void print(std::basic_ostream<Ch>& os, const T& v)
					{
						static_assert(fake_dependency<T>::value, "Type is not supported for printing");
					}
				};

				template<template<class> class H, typename T> struct pretty_head
				{
					template<typename Ch> static void print(std::basic_ostream<Ch>& os, const T& v)
					{
						H<T>::preformat(os);
						H<T>::bounce(os, v);
					}
				};

				template<template<class> class H> struct pretty_head<H, void>
				{
					template<typename Ch> static void print(std::basic_ostream<Ch>& os)
					{
						H<void>::preformat(os);
						H<void>::bounce(os);
					}
				};

				struct simple_formatter
				{
					template<typename Ch> static void preformat(std::basic_ostream<Ch>& os)
					{
						put_structure_space(os);
					}
				};

				struct object_formatter
				{
					template<typename Ch> static void preformat(std::basic_ostream<Ch>& os)
					{
						put_structure_newline(os);
					}
				};
			}
		}
	}
}

#endif // PELI_DETAIL_PRINTER_HEAD_H
