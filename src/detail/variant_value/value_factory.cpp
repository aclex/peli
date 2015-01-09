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

#include "peli/detail/variant_value/value_factory.h"

#include "detail/parser/tokenizer.h"

#include "detail/printer/printer.h"

using namespace std;

using namespace peli;

using namespace peli::detail;

using namespace peli::detail::variant_value;

value_factory::value_type* value_factory::parse(istream& is)
{
	return parser::tokenizer<value_factory>::tok(is);
}

value_factory::value_type* value_factory::parse(wistream& is)
{
	return parser::tokenizer<value_factory>::tok(is);
}

void value_factory::print(ostream& os, const value_factory::value_type* v)
{
	if (!v)
		return;

	printer::printer p(os);
	v->print(&p);
}

void value_factory::print(wostream& os, const value_factory::value_type* v)
{
	if (!v)
		return;

	printer::wprinter p(os);
	v->print(&p);
}