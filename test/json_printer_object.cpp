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

bool check_empty()
{
	const string str1 = "{}";
	const wstring str2 = L"{}";

	const string str1_pretty = "{ }";
	const wstring str2_pretty = L"{ }";

	ostringstream os1;
	wostringstream os2;

	const json::object ch1;
	json::value v1(ch1);
	const json::wobject ch2;
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

	os1 << json::pretty << v1;
	os2 << json::pretty << v2;

	if (os1.str() != str1_pretty)
		return false;

	if (os2.str() != str2_pretty)
		return false;

	return true;
}

bool check_one()
{
	const string str1 = "{\"a\":null}";
	const wstring str2 = L"{\"a\":null}";

	const string str1_pretty = "{\n\t\"a\" : null\n}";
	const wstring str2_pretty = L"{\n\t\"a\" : null\n}";

	ostringstream os1;
	wostringstream os2;

	const json::object ch1 { { "a"s, json::value() } };
	json::value v1(ch1);
	const json::wobject ch2 { { L"a"s, json::wvalue() } };
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

	os1 << json::pretty << v1;
	os2 << json::pretty << v2;

	if (os1.str() != str1_pretty)
		return false;

	if (os2.str() != str2_pretty)
		return false;

	return true;
}

bool check_two()
{
	const string str1 = "{\"a\":null,\"b\":null}";
	const wstring str2 = L"{\"a\":null,\"b\":null}";
	const string str1_pretty = "{\n\t\"a\" : null,\n\t\"b\" : null\n}";
	const wstring str2_pretty = L"{\n\t\"a\" : null,\n\t\"b\" : null\n}";

	ostringstream os1;
	wostringstream os2;

	json::object ch1 { { "a"s, json::value() }, { "b"s, json::value() } };
	json::value v1(ch1);
	json::wobject ch2 { { L"a"s, json::wvalue() }, { L"b"s, json::wvalue() } };
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

	os1 << json::pretty << v1;
	os2 << json::pretty << v2;

	if (os1.str() != str1_pretty)
		return false;

	if (os2.str() != str2_pretty)
		return false;

	return true;
}

bool check_nested()
{
	const string str1 = "{\"a\":null,\"b\":{\"ba\":null},\"c\":null}";
	const wstring str2 = L"{\"a\":null,\"b\":{\"ba\":null},\"c\":null}";
	const string str1_pretty = "{\n\t\"a\" : null,\n\t\"b\" :\n\t{\n\t\t\"ba\" : null\n\t},\n\t\"c\" : null\n}";
	const wstring str2_pretty = L"{\n\t\"a\" : null,\n\t\"b\" :\n\t{\n\t\t\"ba\" : null\n\t},\n\t\"c\" : null\n}";

	ostringstream os1;
	wostringstream os2;

	json::object ch1 { { "a"s, json::value() }, { "b"s, json::object { { "ba"s, json::value() } } }, { "c"s, json::value() } };
	json::value v1(ch1);
	json::wobject ch2 { { L"a"s, json::wvalue() }, { L"b"s, json::wobject { { L"ba"s, json::wvalue() } } }, { L"c"s, json::wvalue() } };
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

	os1 << json::pretty << v1;
	os2 << json::pretty << v2;

	if (os1.str() != str1_pretty)
		return false;

	if (os2.str() != str2_pretty)
		return false;

	return true;
}

int main(int, char**)
{
	if (!check_empty())
		return 1;

	if (!check_one())
		return 2;

	if (!check_two())
		return 3;

	if (!check_nested())
		return 4;

	return 0;
}
