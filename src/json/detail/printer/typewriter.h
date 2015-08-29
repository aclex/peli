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

#ifndef PELI_DETAIL_PRINTER_TYPEWRITER_H
#define PELI_DETAIL_PRINTER_TYPEWRITER_H

#include <ostream>
#include <streambuf>
#include <cstddef>

namespace peli
{
	namespace json
	{
		class value;

		namespace detail
		{
			namespace printer
			{
				template<typename Ch, typename Visitor> class typewriter
				{
				public:
					typedef Ch char_type;

					std::basic_streambuf<Ch>* const rdbuf;
					const bool pretty;
					std::size_t tab_level;
					bool need_structure_newline;

					explicit typewriter(std::basic_ostream<Ch>& os);
					template<typename U> void print(const U& v);
					void print();
					void print(const json::value& v);
				};
			}
		}
	}
}

#include "json/detail/printer/typewriter.tcc" // template definition

#endif // PELI_DETAIL_PRINTER_TYPEWRITER_H
