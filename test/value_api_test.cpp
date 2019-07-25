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

#include <iostream>

#include "peli/json/value.h"

using namespace std;

using namespace peli;

int main(int, char**)
{
	json::object obj;
	obj["object"] = json::make_value<json::object>();

	json::object& inner_obj(get<json::object>(obj["object"]));
	inner_obj["inner_number"] = json::number { 42 };
	obj["array"] = json::array { json::number { 433.52 }, "string_value"s };

	json::array& arr(get<json::array>(obj["array"]));

	obj["boolean"] = json::make_value<bool>();
	obj["boolean"] = true;

	obj["null"] = json::value();

	if (!get<bool>(obj["boolean"]))
		return -1;

	if (get<json::number>(inner_obj["inner_number"]) != 42)
		return -2;

	if (get<json::number>(arr[0]) != 433.52)
		return -3;

	if (get<string>(arr[1]) != "string_value")
		return -4;

	return 0;
}
