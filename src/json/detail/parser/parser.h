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

#ifndef PELI_DETAIL_PARSER_PARSER_H
#define PELI_DETAIL_PARSER_PARSER_H

#include <streambuf>
#include <array>

namespace peli
{
	namespace json
	{
		namespace detail
		{
			namespace parser
			{
				template<class JsonType> class parser
				{
					template<class> struct fake_dependency : public std::false_type { };

				public:
					template<typename Ch>
					static JsonType parse(std::basic_streambuf<Ch>*)
					{
						static_assert(fake_dependency<JsonType>::value, "Type is not supported for parsing");
					}
				};
			}
		}
	}
}

#endif // PELI_DETAIL_PARSER_PARSER_H
