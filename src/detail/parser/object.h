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

#ifndef PELI_DETAIL_PARSER_OBJECT_H
#define PELI_DETAIL_PARSER_OBJECT_H

#include <string>
#include <stdexcept>

#include <peli/json/value.h>
#include <peli/json/object.h>

#include "detail/parser/parser.h"

namespace peli
{
	namespace detail
	{
		namespace parser
		{
			template<> class parser<peli::json::object>
			{
			public:
				template<typename Ch, typename Alloc>
				static typename peli::json::object parse(std::basic_istream<Ch, Alloc>& is)
				{
					peli::json::object obj;

					if (is.peek() != 0x7b) // '{'
						throw std::runtime_error("");

					is.get();

					skip_whitespace(is);

					if (is.peek() != 0x7d) // '}'
					{
						if (is.peek() != 0x22) // '"'
							throw std::runtime_error("");

						while (true)
						{
							auto id = parser<std::basic_string<Ch>>::parse(is);

							skip_whitespace(is);

							if (is.peek() != 0x3a) // ':'
								throw std::runtime_error("");

							is.get();

							skip_whitespace(is);

							json::value v;
							is >> v;
							obj[id] = v;

							skip_whitespace(is);

							if (is.peek() == 0x7d) // '}'
							{
								is.get();
								break;
							}

							if (is.peek() != 0x2c) // ','
							{
								throw std::runtime_error("");
							}

							is.get();

							skip_whitespace(is);
						}
					}
					else
					{
						is.get();
					}

					return obj;
				}
			};
		}
	}
}

#endif // PELI_DETAIL_PARSER_OBJECT_H
