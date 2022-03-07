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
	const string str1 = "[]";
	const wstring str2 = L"[]";

	const string str1_pretty = "[]";
	const wstring str2_pretty = L"[]";

	ostringstream os1;
	wostringstream os2;

	const json::array ch1;
	json::value v1(ch1);

	const json::warray ch2;
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
	const string str1 = "[null]";
	const wstring str2 = L"[null]";

	const string str1_pretty = "[\n\tnull\n]";
	const wstring str2_pretty = L"[\n\tnull\n]";

	ostringstream os1;
	wostringstream os2;

	const json::array ch1 { json::value() };
	json::value v1(ch1);

	const json::warray ch2 { json::wvalue() };
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


	cout << "test:" << endl;
	cout << os1.str() << endl;
	if (os1.str() != str1_pretty)
		return false;

	if (os2.str() != str2_pretty)
		return false;

	return true;
}

bool check_two()
{
	const string str1 = "[null,null]";
	const wstring str2 = L"[null,null]";
	const string str1_pretty = "[\n\tnull,\n\tnull\n]";
	const wstring str2_pretty = L"[\n\tnull,\n\tnull\n]";

	ostringstream os1;
	wostringstream os2;

	json::array ch1 { json::value(), json::value() };
	json::value v1(ch1);

	json::warray ch2 { json::wvalue(), json::wvalue() };
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
	const string str1 = "[null,[null],null]";
	const wstring str2 = L"[null,[null],null]";
	const string str1_pretty = "[\n\tnull,\n\t[\n\t\tnull\n\t],\n\tnull\n]";
	const wstring str2_pretty = L"[\n\tnull,\n\t[\n\t\tnull\n\t],\n\tnull\n]";

	ostringstream os1;
	wostringstream os2;

	json::array ch1 { json::value(), json::value(json::array {json::value() }), json::value() };
	json::value v1(ch1);

	json::warray ch2 { json::wvalue(), json::wvalue(json::warray {json::wvalue() }), json::wvalue() };
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

	cout << "test:" << endl;
	cout << os1.str() << endl;
	cout << "str:" << endl;
	cout << str1_pretty << endl;
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
