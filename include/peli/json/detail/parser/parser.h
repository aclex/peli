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

#ifndef PELI_DETAIL_PARSER_PARSER_H
#define PELI_DETAIL_PARSER_PARSER_H

#include <streambuf>
#include <array>

namespace peli
{
	namespace json
	{
		namespace detail
		{
			namespace parser
			{
				/** \brief [JSON](https://json.org) entity parser template.
				 *
				 * Per-type specializations of this template define the parsing
				 * process of the corresponding types.
				 */
				template<class JsonType> class parser
				{
					/** \brief Fake dependency type to run `static_assert` correctly. */
					template<class> struct fake_dependency : public std::false_type { };

				public:
					/** \brief Parsing function.
					 *
					 * Fails to compiled, if called for anything other than
					 * [JSON](https://json.org) type.
					 *
					 * \tparam InputBuffer input buffer adapter.
					 */
					template<class InputBuffer>
					static JsonType parse(InputBuffer&)
					{
						static_assert(fake_dependency<JsonType>::value, "Type is not supported for parsing");
					}
				};
			}
		}
	}
}

#endif // PELI_DETAIL_PARSER_PARSER_H
