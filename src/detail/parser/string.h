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

#ifndef PELI_DETAIL_PARSER_STRING_H
#define PELI_DETAIL_PARSER_STRING_H

#include <string>
#include <stdexcept>

#include <peli/json/array.h>

#include "detail/parser/parser.h"

namespace peli
{
	namespace detail
	{
		namespace parser
		{
			template<typename Ch> class parser<std::basic_string<Ch>>
			{
			public:
				static typename std::basic_string<Ch> parse(std::basic_istream<Ch>& is)
				{
					std::basic_string<Ch> ret;

					if (is.peek() != 0x22) // '"'
						throw std::runtime_error("");

					is.get();

					while (is.peek() != 0x22)
						ret += is.get();

					is.get();

					return ret;
				}
			};
		}
	}
}

#endif // PELI_DETAIL_PARSER_STRING_H
