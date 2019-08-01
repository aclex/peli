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

#ifndef PELI_DETAIL_PARSER_TOKENIZER_H
#define PELI_DETAIL_PARSER_TOKENIZER_H

#include <istream>
#include <streambuf>

namespace peli
{
	namespace json
	{
		namespace detail
		{
			/** \brief [JSON](https://json.org) parsing part. */
			namespace parser
			{
				/** \brief Reads input, splits to [JSON](https://json.org) tokens and send them to parsing. */
				class tokenizer
				{
				public:
					/** \brief Main tokenizing method.
					 *
					 * \tparam Ch character type of the stream.
					 *
					 * \param rdbuf read buffer of the input stream.
					 *
					 * \return `basic_value` with representation of the consumed
					 * and parsed [JSON](https://json.org) subtree.
					 *
					 */
					template<typename Ch> static json::basic_value<Ch> tok(std::basic_streambuf<Ch>* rdbuf);

					/** \brief Interface function receiving stream as its input.
					 *
					 * Does additional stream-related checks and redirects to `tok`.
					 */
					template<typename Ch, typename Alloc> static json::basic_value<Ch> gentle_stream(std::basic_istream<Ch, Alloc>& is);
				};
			}
		}
	}
}

#include "peli/json/detail/parser/tokenizer.tcc" // template definition

#endif // PELI_DETAIL_PARSER_TOKENIZER_H
