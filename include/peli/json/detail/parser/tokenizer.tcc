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

#include "peli/json/value.h"

#include "peli/json/detail/special_chars.h"

#include "peli/json/detail/parser/object.h"
#include "peli/json/detail/parser/array.h"
#include "peli/json/detail/parser/string.h"
#include "peli/json/detail/parser/number.h"
#include "peli/json/detail/parser/boolean.h"
#include "peli/json/detail/parser/null.h"

#include "peli/json/detail/parser/stream_routines.h"

template<typename Ch> peli::json::basic_value<Ch> peli::json::detail::parser::tokenizer::tok(std::basic_streambuf<Ch>* rdbuf)
{
	using namespace peli::json;

	using namespace peli::json::detail;
	using namespace peli::json::detail::parser;

	skip_whitespace(rdbuf);

	typename std::basic_streambuf<Ch>::int_type next_char = rdbuf->sgetc();

	switch (next_char)
	{
	case special_chars::left_curly:
		return basic_value<Ch>(parser<basic_object<Ch>>::parse(rdbuf));

	case special_chars::left_square:
		return basic_value<Ch>(parser<basic_array<Ch>>::parse(rdbuf));

	case special_chars::quote:
		return basic_value<Ch>(parser<std::basic_string<Ch>>::parse(rdbuf));

	case special_chars::n:
		parser<void>::parse(rdbuf);
		return basic_value<Ch>();

	case special_chars::t:
	case special_chars::f:
		return basic_value<Ch>(parser<bool>::parse(rdbuf));

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
		return basic_value<Ch>(parser<number>::parse(rdbuf));

	default:
		return basic_value<Ch>();
	}
}


template<typename Ch, typename Alloc> peli::json::basic_value<Ch> peli::json::detail::parser::tokenizer::gentle_stream(std::basic_istream<Ch, Alloc>& is)
{
	if (!typename std::basic_istream<Ch, Alloc>::sentry(is, true))
	{
		return peli::json::basic_value<Ch> { };
	}

	return peli::json::detail::parser::tokenizer::tok(is.rdbuf());
}
