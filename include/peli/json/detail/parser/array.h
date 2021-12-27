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

						while (t != std::basic_streambuf<char_type>::traits_type::eof())
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
