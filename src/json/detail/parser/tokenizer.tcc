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
#include "json/value.h"


#include "json/detail/special_chars.h"

#include "json/detail/parser/object.h"
#include "json/detail/parser/array.h"
#include "json/detail/parser/string.h"
#include "json/detail/parser/number.h"
#include "json/detail/parser/boolean.h"
#include "json/detail/parser/null.h"

#include "json/detail/parser/stream_routines.h"

template<typename Ch, typename Alloc> peli::json::value peli::json::detail::parser::tokenizer::tok(std::basic_istream<Ch, Alloc>& is)
{
	using namespace peli::json;
	using namespace peli::detail;
	using namespace peli::json::detail;
	using namespace peli::json::detail::parser;

	skip_whitespace(is);

	Ch next_char = is.peek();

	switch (next_char)
	{
	case special_chars::left_curly:
		return value(parser<basic_object<Ch>>::parse(is));

	case special_chars::left_square:
		return value(parser<array>::parse(is));

	case special_chars::quote:
		return value(parser<std::basic_string<Ch>>::parse(is));

	case special_chars::n:
		parser<void>::parse(is);
		return value();

	case special_chars::t:
	case special_chars::f:
		return value(parser<bool>::parse(is));

	default:
		return value(parser<number>::parse(is));
	}

	throw std::invalid_argument("");
}
