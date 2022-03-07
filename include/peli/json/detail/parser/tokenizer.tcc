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

#include "peli/json/value.h"

#include "peli/json/detail/special_chars.h"

#include "peli/json/detail/parser/object.h"
#include "peli/json/detail/parser/array.h"
#include "peli/json/detail/parser/string.h"
#include "peli/json/detail/parser/number.h"
#include "peli/json/detail/parser/boolean.h"
#include "peli/json/detail/parser/null.h"

#include "peli/json/detail/parser/stream_routines.h"

template<class InputBuffer> peli::json::basic_value<typename InputBuffer::char_type> peli::json::detail::parser::tokenizer::tok(InputBuffer& buf)
{
	using namespace peli::json;

	using namespace peli::json::detail;
	using namespace peli::json::detail::parser;

	using char_type = typename InputBuffer::char_type;

	skip_whitespace(buf);

	const auto next_char { buf.getc() };

	switch (next_char)
	{
	case special_chars::left_curly:
		return basic_value<char_type>(parser<basic_object<char_type>>::parse(buf));

	case special_chars::left_square:
		return basic_value<char_type>(parser<basic_array<char_type>>::parse(buf));

	case special_chars::quote:
		return basic_value<char_type>(parser<std::basic_string<char_type>>::parse(buf));

	case special_chars::n:
		parser<void>::parse(buf);
		return basic_value<char_type>();

	case special_chars::t:
	case special_chars::f:
		return basic_value<char_type>(parser<bool>::parse(buf));

	case special_chars::minus:
	case special_chars::d0:
	case special_chars::d1:
	case special_chars::d2:
	case special_chars::d3:
	case special_chars::d4:
	case special_chars::d5:
	case special_chars::d6:
	case special_chars::d7:
	case special_chars::d8:
	case special_chars::d9:
		return basic_value<char_type>(parser<number>::parse(buf));

	default:
		return basic_value<char_type>();
	}
}
