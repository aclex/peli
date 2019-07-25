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

using namespace std;

using namespace peli;

int check_empty()
{
	const string str1 = "   {\n\t   }\r\n  ";
	const wstring str2 = L"{  \r\t   }\n\t  \n  \n\r  ";

	istringstream is1(str1);
	json::value v1;
	is1 >> v1;

	wistringstream is2(str2);
	json::wvalue v2;
	is2 >> v2;

	const json::object& obj1(get<json::object>(v1));
	const json::wobject& obj2(get<json::wobject>(v2));
	json::object ch1;
	json::wobject ch2;

	if (obj1 != ch1)
		return -1;

	if (obj2 != ch2)
		return -2;

	return 0;
}

int check_one()
{
	const string str1 = "   {\n\t\"a\"\n\n\t\r:   null}\r\n  ";
	const wstring str2 = L"{  \r\t \"a\"\n\n\t\r:   null  }\n\t  \n  \n\r  ";

	istringstream is1(str1);
	json::value v1;
	is1 >> v1;

	wistringstream is2(str2);
	json::wvalue v2;
	is2 >> v2;

	const json::object& obj1(get<json::object>(v1));
	const json::wobject& obj2(get<json::wobject>(v2));
	json::object ch1 { { "a"s, json::value() } };
	json::wobject ch2 { { L"a"s, json::wvalue() } };

	if (obj1 != ch1)
		return -3;

	if (obj2 != ch2)
		return -4;

	return 0;
}

int check_two()
{
	const string str1 = "   {\n\t\"a\"\n\n\t\r:   null \n\n\r  ,\"b\": \t\tnull}\r\n  ";
	const wstring str2 = L"{  \r\t \"a\"\n\n\t\r:   null  \n\n\r  ,\"b\": \r\tnull }\n\t  \n  \n\r  ";

	istringstream is1(str1);
	json::value v1;
	is1 >> v1;

	wistringstream is2(str2);
	json::wvalue v2;
	is2 >> v2;

	const json::object& obj1(get<json::object>(v1));
	const json::wobject& obj2(get<json::wobject>(v2));
	json::object ch1 { { "a"s, json::value() }, { "b"s, json::value() } };
	json::wobject ch2 { { L"a"s, json::wvalue() }, { L"b"s, json::wvalue() } };

	if (obj1 != ch1)
		return -5;

	if (obj2 != ch2)
		return -6;

	return 0;
}

int check_redundant()
{
	const string str1 = "   {\n\t\"a\"\n\n\t\r:   null \n\n\r  ,\n\t\"a\"\n\n\t\r:   {   } \n\n,\r \"b\": \t\tnull}\r\n  ";
	const wstring str2 = L"{  \r\t \"a\"\n\n\t\r:   null  \n\n\r  ,\n\t\"a\"\n\n\t\r:   {   } \n\n,\r\"b\": \r\tnull }\n\t  \n  \n\r  ";

	istringstream is1(str1);
	json::value v1;
	is1 >> v1;

	wistringstream is2(str2);
	json::wvalue v2;
	is2 >> v2;

	const json::object& obj1(get<json::object>(v1));
	const json::wobject& obj2(get<json::wobject>(v2));
	json::object ch1 { { "a"s, json::value() }, { "b"s, json::value() } };
	json::wobject ch2 { { L"a"s, json::wvalue() }, { L"b"s, json::wvalue() } };

	if (obj1 != ch1)
		return -7;

	if (obj2 != ch2)
		return -8;

	return 0;
}

int main(int, char**)
{
	const int er = check_empty();

	if (er)
		return er;

	const int nr = check_one();

	if (nr)
		return nr;

	const int tr = check_two();

	if (tr)
		return tr;

	const int rr = check_redundant();

	return rr;
}
