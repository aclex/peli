/*
 * This file is part of Peli - universal JSON interaction library
 * Copyright (C) 2014-2022  Alexey Chernov <4ernov@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
