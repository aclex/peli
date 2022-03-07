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
