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

#include "exception_check.h"

using namespace std;

using namespace peli;
using namespace peli::test;

int check()
{
	const string str1 = "   [\n\tnull   ]\r\n  ";
	const wstring str2 = L"[  \r\tnull   ]\n\t  \n  \n\r  ";

	istringstream is1(str1);
	json::value v1;
	is1 >> v1;

	wistringstream is2(str2);
	json::wvalue v2;
	is2 >> v2;

	const json::array& obj1(get<json::array>(v1));
	const json::warray& obj2(get<json::warray>(v2));
	json::array ch1 { json::value() };
	json::warray ch2 { json::wvalue() };

	if (obj1 != ch1)
		return 1;

	if (obj2 != ch2)
		return 2;

	if (!obj1[0].null())
		return 3;

	return 0;
}

int check_typos()
{
	if (!has_thrown_on<parse_error>("[nil]"))
		return 4;

	if (!has_thrown_on<parse_error>("[nuul]"))
		return 5;

	if (!has_thrown_on<parse_error>("[nul]"))
		return 6;

	if (!has_null_return("cde"))
		return 7;

	return 0;
}

int main(int, char**)
{
	if (const auto r = check())
	{
		return r;
	}

	if (const auto r = check_typos())
	{
		return r;
	}

	return 0;
}
