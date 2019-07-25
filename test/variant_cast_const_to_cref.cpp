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

using namespace std;

using namespace peli;

int main(int, char**)
{
	json::object obj1;
	obj1["test"] = json::number { 52 };
	const json::value v1(obj1);

	const json::object& obj2(get<json::object>(v1));
	json::object obj3(get<json::object>(v1));

	if (obj2 != obj1)
		return -1;

	if (obj3 != obj1)
		return -2;

	obj3["foo"] = "bar"s;

	if (obj3 == obj1)
		return -3;

	if (obj3 == obj2)
		return -4;

	return 0;
}
