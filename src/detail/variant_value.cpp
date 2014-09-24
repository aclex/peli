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

#include "peli/detail/variant_value.h"

#include <stdexcept>

#include "peli/bad_value_cast.h"

using namespace std;

using namespace peli;
using namespace peli::detail;

object variant_value::variant_as(typename object_type_tag::type tag) const
{
	bad_as(object_type_tag::name);
}

peli::array variant_value::variant_as(typename array_type_tag::type tag) const
{
	bad_as(array_type_tag::name);
}

int variant_value::variant_as(typename number_type_tag::type tag) const
{
	bad_as(number_type_tag::name);
}

double variant_value::variant_as(typename real_type_tag::type tag) const
{
	bad_as(real_type_tag::name);
}

bool variant_value::variant_as(typename boolean_type_tag::type tag) const
{
	bad_as(boolean_type_tag::name);
}

string variant_value::type_name() const
{
	return "unknown";
}

void variant_value::bad_as(const string& requested_type_name) const
{
	throw bad_value_cast(requested_type_name, type_name());
}
