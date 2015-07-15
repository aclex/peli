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
					template<typename Ch> static bool parse(std::basic_istream<Ch>& is)
					{
						bool ret = false;
						Ch c = is.get();
						switch (c)
						{
						case special_chars::t:
							c = is.get();
							if (c != special_chars::r)
							{
								is.unget();
								throw std::invalid_argument("");
							}

							c = is.get();

							if (c != special_chars::u)
							{
								is.unget();
								throw std::invalid_argument("");
							}

							c = is.get();

							if (c != special_chars::e)
							{
								is.unget();
								throw std::invalid_argument("");
							}

							ret = true;
							break;

						case special_chars::f:
							c = is.get();
							if (c != special_chars::a)
							{
								is.unget();
								throw std::invalid_argument("");
							}

							c = is.get();

							if (c != special_chars::l)
							{
								is.unget();
								throw std::invalid_argument("");
							}

							c = is.get();

							if (c != special_chars::s)
							{
								is.unget();
								throw std::invalid_argument("");
							}

							c = is.get();

							if (c != special_chars::e)
							{
								is.unget();
								throw std::invalid_argument("");
							}

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
