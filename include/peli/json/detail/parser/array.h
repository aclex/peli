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

#include <stdexcept>

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
					static typename peli::json::basic_array<Ch> parse(std::basic_streambuf<Ch>* rdbuf)
					{
						peli::json::basic_array<Ch> arr;

						typename std::basic_streambuf<Ch>::int_type t = rdbuf->sgetc();
						if (t != special_chars::left_square)
							throw std::runtime_error("");

						rdbuf->sbumpc();

						skip_whitespace(rdbuf);

						t = rdbuf->sgetc();
						if (t == special_chars::right_square)
						{
							rdbuf->sbumpc();
							return arr;
						}

						while (t != std::basic_streambuf<Ch>::traits_type::eof())
						{
							arr.emplace_back(tokenizer::tok(rdbuf));

							skip_whitespace(rdbuf);

							t = rdbuf->sgetc();
							if (t == special_chars::right_square)
							{
								rdbuf->sbumpc();
								break;
							}

							if (t != special_chars::comma)
								throw std::runtime_error("");

							rdbuf->sbumpc();

							skip_whitespace(rdbuf);
						}

						return arr;
					}
				};
			}
		}
	}
}

#endif // PELI_DETAIL_PARSER_ARRAY_H
