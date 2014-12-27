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

#ifndef PELI_DETAIL_PARSER_ARRAY_H
#define PELI_DETAIL_PARSER_ARRAY_H

#include <stdexcept>

#include <peli/json/array.h>

#include "detail/parser/parser.h"

namespace peli
{
	namespace detail
	{
		namespace parser
		{
			template<> class parser<peli::json::array>
			{
			public:
				template<typename Ch, typename Alloc>
				static typename peli::json::array parse(std::basic_istream<Ch, Alloc>& is)
				{
					peli::json::array arr;

					if (is.peek() != 0x5b) // '['
						throw std::runtime_error("");

					is.get();

					skip_whitespace(is);

					if (is.peek() == 0x5d) // ']'
					{
						is.get();
						return arr;
					}

					while (true)
					{
						json::value v;
						is >> v;

						arr.push_back(v);

						if (is.peek() == 0x5d) // ']'
						{
							is.get();
							break;
						}

						if (is.peek() != 0x2c) // ','
						{
							throw std::runtime_error("");
						}

						skip_whitespace(is);
					}

					return arr;
				}
			};
		}
	}
}

#endif // PELI_DETAIL_PARSER_ARRAY_H
