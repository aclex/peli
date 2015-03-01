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

#include <istream>

#include "detail/special_chars.h"

#include "detail/parser/object.h"
#include "detail/parser/array.h"
#include "detail/parser/string.h"
#include "detail/parser/number.h"
#include "detail/parser/boolean.h"
#include "detail/parser/null.h"

#include "detail/parser/stream_routines.h"

#ifndef PELI_DETAIL_PARSER_TOKENIZER_H
#define PELI_DETAIL_PARSER_TOKENIZER_H

namespace peli
{
	namespace detail
	{
		namespace parser
		{
			template<typename FactoryType> class tokenizer
			{
			public:
				template<typename Ch, typename Alloc> static
				typename FactoryType::value_type* tok(std::basic_istream<Ch, Alloc>& is)
				{
					skip_whitespace(is);

					Ch next_char = is.peek();

					switch (next_char)
					{
					case special_chars::left_curly:
					{
						return FactoryType::create(parser<peli::json::basic_object<Ch>>::parse(is));
					}

					case special_chars::left_square:
						return FactoryType::create(parser<peli::json::array>::parse(is));

					case special_chars::quote:
						return FactoryType::create(parser<std::basic_string<Ch>>::parse(is));

					case special_chars::n:
						parser<void>::parse(is);
						break;

					case special_chars::t:
					case special_chars::f:
						return FactoryType::create(parser<bool>::parse(is));
						break;

					default:
						return FactoryType::create(parser<peli::json::number>::parse(is));
						break;
					}

					return nullptr;
				}
			};
		}
	}
}

#endif // PELI_DETAIL_PARSER_TOKENIZER_H
