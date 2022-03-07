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

using namespace std;

using namespace peli;

int main(int, char**)
{
	json::object a;
	json::value v1(a);
	json::object& obj1(get<json::object>(v1));
	obj1["test"] = json::number { 52 };

	json::value v2(v1);

	if (v1 != v2)
		return 1;

	json::object& obj2(get<json::object>(v2));
	obj2["test"] = json::number { 53 };

	if (v1 == v2)
		return 2;

	return 0;
}
