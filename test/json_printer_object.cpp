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
