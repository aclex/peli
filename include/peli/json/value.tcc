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

#include "peli/json/detail/parser/stream_buffer.h"
#include "peli/json/detail/parser/string_buffer.h"
#include "peli/json/detail/parser/tokenizer.h"
#include "peli/json/detail/printer/visitor.h"

namespace peli
{
	namespace json
	{
		template<typename Ch>
		inline std::basic_istream<Ch>& operator>>(std::basic_istream<Ch>& is, basic_value<Ch>& v)
		{
			peli::json::detail::parser::stream_buffer<Ch> buf { is };
			v = peli::json::detail::parser::tokenizer::tok(buf);

			return is;
		}

		template<typename Ch>
		inline std::basic_ostream<Ch>& operator<<(std::basic_ostream<Ch>& os, const basic_value<Ch>& v)
		{
			peli::json::detail::printer::stream_visitor<Ch> print_visitor(os);

			peli::visit(print_visitor, v);

			return os;
		}

		template<typename Ch>
		basic_value<Ch> basic_value<Ch>::parse(const Ch* const str)
		{
			peli::json::detail::parser::char_buffer<Ch> buf { str };
			return peli::json::detail::parser::tokenizer::tok(buf);
		}

		template<typename Ch>
		basic_value<Ch> basic_value<Ch>::parse(const std::basic_string<Ch>& str)
		{
			peli::json::detail::parser::string_buffer<Ch> buf { str };
			return peli::json::detail::parser::tokenizer::tok(buf);
		}

#ifdef CXX_STD_17
		template<typename Ch>
		basic_value<Ch> basic_value<Ch>::parse(const std::basic_string_view<Ch> sv)
		{
			peli::json::detail::parser::string_view_buffer<Ch> buf { sv };
			return peli::json::detail::parser::tokenizer::tok(buf);
		}
#endif

		template<typename Ch>
		std::basic_string<Ch> to_string(const basic_value<Ch>& v, const bool pretty)
		{
			std::basic_string<Ch> result;

			peli::json::detail::printer::string_visitor<Ch> print_visitor(result, pretty);

			peli::visit(print_visitor, v);

			return result;
		}
	}
}
