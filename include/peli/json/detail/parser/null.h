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

#ifndef PELI_DETAIL_PARSER_NULL_H
#define PELI_DETAIL_PARSER_NULL_H

#include <string>
#include <stdexcept>

#include "peli/json/value.h"
#include "peli/json/object.h"

#include "peli/json/detail/special_chars.h"

#include "peli/json/detail/parser/parser.h"

namespace peli
{
	namespace json
	{
		namespace detail
		{
			namespace parser
			{
				template<> class parser<void>
				{
				public:
					template<typename Ch> static void parse(std::basic_streambuf<Ch>* rdbuf)
					{
						typename std::basic_streambuf<Ch>::int_type c = rdbuf->sgetc();
						if (c != special_chars::n)
							throw std::invalid_argument("");

						c = rdbuf->snextc();

						if (c != special_chars::u)
							throw std::invalid_argument("");

						c = rdbuf->snextc();

						if (c != special_chars::l)
							throw std::invalid_argument("");

						c = rdbuf->snextc();

						if (c != special_chars::l)
							throw std::invalid_argument("");

						rdbuf->sbumpc();
					}
				};
			}
		}
	}
}

#endif // PELI_DETAIL_PARSER_NULL_H