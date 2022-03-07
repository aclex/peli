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

#include <sstream>
#include <iostream>

#include "peli/json/value.h"
#include "peli/json/iomanip.h"

using namespace std;

using namespace peli;

bool check_boolean()
{
	const string str1 = "[true,false,true,true]";
	const wstring str2 = L"[true,false,true,true]";

	ostringstream os1;
	wostringstream os2;

	json::array ch1 { json::value(true), json::value(false), json::value(true), json::value(true) };
	json::value v1(ch1);
	json::warray ch2 { json::wvalue(true), json::wvalue(false), json::wvalue(true), json::wvalue(true) };
	json::wvalue v2(ch2);

	os1 << v1;
	os2 << v2;

	if (os1.str() != str1)
		return false;

	if (os2.str() != str2)
		return false;

	os1.clear();
	os1.seekp(0);
	os2.clear();
	os2.seekp(0);

	return true;
}

int main(int, char**)
{
	if (!check_boolean())
		return 1;

	return 0;
}
