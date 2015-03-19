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

#include <cassert>

#include "peli/detail/variant_value/value_factory.h"
#include "peli/detail/variant_value/value_holder_template.h"

using namespace std;

using namespace peli;

int main(int argc, char* argv[])
{
	typedef json::number target_type;

	const detail::variant_value::value_holder* holder = new detail::variant_value::value_holder_template<target_type>();
	target_type test1 = detail::variant_value::value_factory::cast<target_type>(holder);

	return 0;
}