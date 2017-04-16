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

#include "peli/json/value.h"

using namespace std;

using namespace peli;

int main(int, char**)
{
	json::value v1(json::make_value<json::object>());
	json::object& obj1(v1);
	obj1["test"] = json::value(52);

	json::object obj2 = static_cast<json::object>(v1);
	json::object obj3(v1);

	assert(obj2 == obj1);
	assert(obj3 == obj1);

	obj3["foo"] = json::value("bar");

	assert(obj3 != obj1);
	assert(obj3 != obj2);

	return 0;
}
