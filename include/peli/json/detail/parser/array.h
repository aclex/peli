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

#ifndef PELI_DETAIL_PARSER_ARRAY_H
#define PELI_DETAIL_PARSER_ARRAY_H

#include "peli/except.h"

#include "peli/json/value.h"
#include "peli/json/array.h"

#include "peli/json/detail/special_chars.h"

#include "peli/json/detail/parser/parser.h"
#include "peli/json/detail/parser/stream_routines.h"
#include "peli/json/detail/parser/tokenizer.h"

namespace peli
{
	namespace json
	{
		namespace detail
		{
			namespace parser
			{
				/** \brief `parser` specialization for [JSON](https://json.org) array.
				 * \see `parser`
				 */
				template<typename Ch> class parser<peli::json::basic_array<Ch>>
				{
				public:
					template<class InputBuffer> static peli::json::basic_array<typename InputBuffer::char_type> parse(InputBuffer& buf)
					{
						using char_type = typename InputBuffer::char_type;

						peli::json::basic_array<char_type> arr;

						auto t = buf.getc();
						if (t != special_chars::left_square)
							throw parse_error("Left square bracket is expected.");

						buf.bumpc();

						skip_whitespace(buf);

						t = buf.getc();
						if (t == special_chars::right_square)
						{
							buf.bumpc();
							return arr;
						}

						while (t != InputBuffer::eof())
						{
							arr.emplace_back(tokenizer::tok(buf));

							skip_whitespace(buf);

							t = buf.getc();
							if (t == special_chars::right_square)
							{
								buf.bumpc();
								break;
							}

							if (t != special_chars::comma)
								throw parse_error("Right square bracket or comma is expected.");

							buf.bumpc();

							skip_whitespace(buf);
						}

						return arr;
					}
				};
			}
		}
	}
}

#endif // PELI_DETAIL_PARSER_ARRAY_H
