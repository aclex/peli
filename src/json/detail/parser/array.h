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

#include "json/detail/special_chars.h"

#include "json/detail/parser/parser.h"
#include "json/detail/parser/stream_routines.h"
#include "json/detail/parser/tokenizer.h"

namespace peli
{
	namespace json
	{
		namespace detail
		{
			namespace parser
			{
				template<> class parser<peli::json::array>
				{
				public:
					template<typename Ch, typename Alloc>
					static typename peli::json::array parse(std::basic_istream<Ch, Alloc>& is)
					{
						peli::json::array arr;

						std::basic_streambuf<Ch>* rdbuf = is.rdbuf();

						typename std::basic_streambuf<Ch>::int_type t = rdbuf->sgetc();
						if (t != special_chars::left_square)
							throw std::runtime_error("");

						rdbuf->sbumpc();

						skip_whitespace(is);

						t = rdbuf->sgetc();
						if (t == special_chars::right_square)
						{
							rdbuf->sbumpc();
							return arr;
						}

						static constexpr typename std::basic_streambuf<Ch>::int_type s_eof = std::basic_streambuf<Ch>::traits_type::eof();

						while (t != s_eof)
						{
							arr.emplace_back(tokenizer::tok(is));

							skip_whitespace(is);

							t = rdbuf->sgetc();
							if (t == special_chars::right_square)
							{
								rdbuf->sbumpc();
								break;
							}

							if (t != special_chars::comma)
								throw std::runtime_error("");

							rdbuf->sbumpc();

							skip_whitespace(is);
						}

						return arr;
					}
				};
			}
		}
	}
}

#endif // PELI_DETAIL_PARSER_ARRAY_H
