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
#include "peli/json/number.h"

using namespace std;

using namespace peli;

int main(int, char**)
{
	json::value v(json::make_value<json::number>());

	try
	{
		json::number n(get<json::number>(v));
		n = 42;
		cout << n << endl;
	}
	catch(...)
	{
		return -1;
	}

	return 0;
}
