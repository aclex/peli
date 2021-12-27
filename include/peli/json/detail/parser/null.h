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

#include "peli/except.h"

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
				/** \brief `parser` specialization for [JSON](https://json.org) null terms.
				 * \see `parser`
				 */
				template<> class parser<void>
				{
				public:
					template<class InputBuffer> static void parse(InputBuffer& buf)
					{
						auto c { buf.getc() };
						if (c != special_chars::n)
							throw parse_error("Failed to parse null token.");

						c = buf.nextc();

						if (c != special_chars::u)
							throw parse_error("Failed to parse null token.");

						c = buf.nextc();

						if (c != special_chars::l)
							throw parse_error("Failed to parse null token.");

						c = buf.nextc();

						if (c != special_chars::l)
							throw parse_error("Failed to parse null token.");

						buf.bumpc();
					}
				};
			}
		}
	}
}

#endif // PELI_DETAIL_PARSER_NULL_H
