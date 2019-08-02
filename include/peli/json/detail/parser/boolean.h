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

#ifndef PELI_DETAIL_PARSER_BOOLEAN_H
#define PELI_DETAIL_PARSER_BOOLEAN_H

#include "peli/except.h"

#include "peli/json/detail/parser/parser.h"

#include "peli/json/detail/special_chars.h"

namespace peli
{
	namespace json
	{
		namespace detail
		{
			namespace parser
			{
				/** \brief `parser` specialization for [JSON](https://json.org) boolean values.
				 * \see `parser`
				 */
				template<> class parser<bool>
				{
				public:
					template<typename Ch> static bool parse(std::basic_streambuf<Ch>* rdbuf)
					{
						bool ret = false;

						typename std::basic_streambuf<Ch>::int_type c = rdbuf->sgetc();
						switch (c)
						{
						case special_chars::t:
							c = rdbuf->snextc();
							if (c != special_chars::r)
								throw parse_error("Failed to parse 'true' boolean token.");

							c = rdbuf->snextc();

							if (c != special_chars::u)
								throw parse_error("Failed to parse 'true' boolean token.");

							c = rdbuf->snextc();

							if (c != special_chars::e)
								throw parse_error("Failed to parse 'true' boolean token.");

							rdbuf->sbumpc();

							ret = true;
							break;

						case special_chars::f:
							c = rdbuf->snextc();
							if (c != special_chars::a)
								throw parse_error("Failed to parse 'false' boolean token.");

							c = rdbuf->snextc();

							if (c != special_chars::l)
								throw parse_error("Failed to parse 'false' boolean token.");

							c = rdbuf->snextc();

							if (c != special_chars::s)
								throw parse_error("Failed to parse 'false' boolean token.");

							c = rdbuf->snextc();

							if (c != special_chars::e)
								throw parse_error("Failed to parse 'false' boolean token.");

							rdbuf->sbumpc();

							ret = false;
							break;

						default:
							throw parse_error("Unexpected character while parsing boolean.");
						}

						return ret;
					}
				};
			}
		}
	}
}

#endif // PELI_DETAIL_PARSER_BOOLEAN_H
