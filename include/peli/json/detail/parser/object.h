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

#ifndef PELI_DETAIL_PARSER_OBJECT_H
#define PELI_DETAIL_PARSER_OBJECT_H

#include <string>

#include "peli/except.h"

#include "peli/json/value.h"
#include "peli/json/object.h"

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
				/** \brief `parser` specialization for [JSON](https://json.org) object.
				 * \see `parser`
				 */
				template<typename Ch> class parser<peli::json::basic_object<Ch>>
				{
				public:
					template<class InputBuffer> static typename peli::json::basic_object<typename InputBuffer::char_type> parse(InputBuffer& buf)
					{
						using char_type = typename InputBuffer::char_type;
						peli::json::basic_object<char_type> obj;

						auto t { buf.getc() };

						if (t != special_chars::left_curly)
							throw parse_error("Left curly bracket is expected.");

						buf.bumpc();

						skip_whitespace(buf);

						t = buf.getc();
						if (t != special_chars::right_curly)
						{
							if (t != special_chars::quote)
								throw parse_error("Quotation mark is expected.");

							while (t != InputBuffer::eof())
							{
								auto&& id { parser<std::basic_string<char_type>>::parse(buf) };

								skip_whitespace(buf);

								t = buf.getc();
								if (t != special_chars::colon)
									throw parse_error("Colon is expected.");

								buf.bumpc();

								skip_whitespace(buf);

								obj.emplace(std::move(id), tokenizer::tok(buf));

								skip_whitespace(buf);

								t = buf.getc();
								if (t == special_chars::right_curly)
								{
									buf.bumpc();
									break;
								}

								if (t != special_chars::comma)
									throw parse_error("Comma or right curly bracket is expected.");

								buf.bumpc();

								skip_whitespace(buf);
							}
						}
						else
						{
							buf.bumpc();
						}

						return obj;
					}
				};
			}
		}
	}
}

#endif // PELI_DETAIL_PARSER_OBJECT_H
