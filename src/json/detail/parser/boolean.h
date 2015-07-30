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

#include <stdexcept>

#include "json/detail/parser/parser.h"

#include "json/detail/special_chars.h"

namespace peli
{
	namespace json
	{
		namespace detail
		{
			namespace parser
			{
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
								throw std::invalid_argument("");

							c = rdbuf->snextc();

							if (c != special_chars::u)
								throw std::invalid_argument("");

							c = rdbuf->snextc();

							if (c != special_chars::e)
								throw std::invalid_argument("");

							rdbuf->sbumpc();

							ret = true;
							break;

						case special_chars::f:
							c = rdbuf->snextc();
							if (c != special_chars::a)
								throw std::invalid_argument("");

							c = rdbuf->snextc();

							if (c != special_chars::l)
								throw std::invalid_argument("");

							c = rdbuf->snextc();

							if (c != special_chars::s)
								throw std::invalid_argument("");

							c = rdbuf->snextc();

							if (c != special_chars::e)
								throw std::invalid_argument("");

							rdbuf->sbumpc();

							ret = false;
							break;

						default:
							throw std::invalid_argument("");
						}

						return ret;
					}
				};
			}
		}
	}
}

#endif // PELI_DETAIL_PARSER_BOOLEAN_H
