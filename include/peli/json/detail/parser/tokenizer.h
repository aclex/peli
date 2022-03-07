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

#ifndef PELI_DETAIL_PARSER_TOKENIZER_H
#define PELI_DETAIL_PARSER_TOKENIZER_H

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
					template<class InputBuffer> static json::basic_value<typename InputBuffer::char_type> tok(InputBuffer& buf);
				};
			}
		}
	}
}

#include "peli/json/detail/parser/tokenizer.tcc" // template definition

#endif // PELI_DETAIL_PARSER_TOKENIZER_H
