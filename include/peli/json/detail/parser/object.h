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

#ifndef PELI_DETAIL_PARSER_OBJECT_H
#define PELI_DETAIL_PARSER_OBJECT_H

#include <string>
#include <stdexcept>

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
				template<typename Ch> class parser<peli::json::basic_object<Ch>>
				{
				public:
					static typename peli::json::basic_object<Ch> parse(std::basic_streambuf<Ch>* rdbuf)
					{
						peli::json::basic_object<Ch> obj;

						typename std::basic_streambuf<Ch>::int_type t = rdbuf->sgetc();

						if (t != special_chars::left_curly)
							throw std::invalid_argument("");

						rdbuf->sbumpc();

						skip_whitespace(rdbuf);

						t = rdbuf->sgetc();
						if (t != special_chars::right_curly)
						{
							if (t != special_chars::quote)
								throw std::invalid_argument("");

							while (t != std::basic_streambuf<Ch>::traits_type::eof())
							{
								auto&& id = parser<std::basic_string<Ch>>::parse(rdbuf);

								skip_whitespace(rdbuf);

								t = rdbuf->sgetc();
								if (t != special_chars::colon)
									throw std::invalid_argument("");

								rdbuf->sbumpc();

								skip_whitespace(rdbuf);

								obj.emplace(std::move(id), tokenizer::tok(rdbuf));

								skip_whitespace(rdbuf);

								t = rdbuf->sgetc();
								if (t == special_chars::right_curly)
								{
									rdbuf->sbumpc();
									break;
								}

								if (t != special_chars::comma)
									throw std::invalid_argument("");

								rdbuf->sbumpc();

								skip_whitespace(rdbuf);
							}
						}
						else
						{
							rdbuf->sbumpc();
						}

						return obj;
					}
				};
			}
		}
	}
}

#endif // PELI_DETAIL_PARSER_OBJECT_H
