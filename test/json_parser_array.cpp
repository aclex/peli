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

int check_empty()
{
	const string str1 = "   [\n\t   ]\r\n  ";
	const wstring str2 = L"[  \r\t   ]\n\t  \n  \n\r  ";

	istringstream is1(str1);
	json::value v1;
	is1 >> v1;

	wistringstream is2(str2);
	json::wvalue v2;
	is2 >> v2;

	const json::array& obj1(get<json::array>(v1));
	const json::warray& obj2(get<json::warray>(v2));
	json::array ch1;
	json::warray ch2;

	if (obj1 != ch1)
		return 1;

	if (obj2 != ch2)
		return 2;

	return 0;
}

int check_one()
{
	const string str1 = "   [\n\t\n\n\t\r   null]\r\n  ";
	const wstring str2 = L"[  \r\t \n\n\t\r   null  ]\n\t  \n  \n\r  ";

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
		return 3;

	if (obj2 != ch2)
		return 4;

	return 0;
}

int check_two()
{
	const string str1 = "   [\n\t\"a\"\n\n\t\r,   null \n\n\r  ,\"b\", \t\tnull]\r\n  ";
	const wstring str2 = L"[  \r\t \"a\"\n\n\t\r,   null  \n\n\r  ,\"b\", \r\tnull ]\n\t  \n  \n\r  ";

	istringstream is1(str1);
	json::value v1;
	is1 >> v1;

	wistringstream is2(str2);
	json::wvalue v2;
	is2 >> v2;

	const json::array& obj1(get<json::array>(v1));
	const json::warray& obj2(get<json::warray>(v2));
	json::array ch1 { "a"s, json::value(), "b"s, json::value() };
	json::warray ch2 { L"a"s, json::wvalue(), L"b"s, json::wvalue() };

	if (obj1 != ch1)
		return 5;

	if (obj2 != ch2)
		return 6;

	return 0;
}

int check_typos()
{
	if (!has_thrown_on<parse_error>("[true. false]"))
		return 7;

	return 0;
}

int main(int, char**)
{
	if (const auto r = check_empty())
		return r;

	if (const auto r = check_one())
		return r;

	if (const auto r = check_two())
		return r;

	if (const auto r = check_typos())
		return r;

	return 0;
}
