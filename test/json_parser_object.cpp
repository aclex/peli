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
#include <cassert>
#include <iostream>

#include "peli/json/value.h"

using namespace std;

using namespace peli;

void check_empty()
{
	const string str1 = "   {\n\t   }\r\n  ";
	const wstring str2 = L"{  \r\t   }\n\t  \n  \n\r  ";

	istringstream is1(str1);
	json::value v1;
	is1 >> v1;

	wistringstream is2(str2);
	json::value v2;
	is2 >> v2;

	const json::object& obj1(v1);
	const json::wobject& obj2(v2);
	json::object ch1;
	json::wobject ch2;

	assert(obj1 == ch1);
	assert(obj2 == ch2);
}

void check_one()
{
	const string str1 = "   {\n\t\"a\"\n\n\t\r:   null}\r\n  ";
	const wstring str2 = L"{  \r\t \"a\"\n\n\t\r:   null  }\n\t  \n  \n\r  ";

	istringstream is1(str1);
	json::value v1;
	is1 >> v1;

	wistringstream is2(str2);
	json::value v2;
	is2 >> v2;

	const json::object& obj1(v1);
	const json::wobject& obj2(v2);
	json::object ch1 { { "a", json::value() } };
	json::wobject ch2 { { L"a", json::value() } };

	assert(obj1 == ch1);
	assert(obj2 == ch2);
}

void check_two()
{
	const string str1 = "   {\n\t\"a\"\n\n\t\r:   null \n\n\r  ,\"b\": \t\tnull}\r\n  ";
	const wstring str2 = L"{  \r\t \"a\"\n\n\t\r:   null  \n\n\r  ,\"b\": \r\tnull }\n\t  \n  \n\r  ";

	istringstream is1(str1);
	json::value v1;
	is1 >> v1;

	wistringstream is2(str2);
	json::value v2;
	is2 >> v2;

	const json::object& obj1(v1);
	const json::wobject& obj2(v2);
	json::object ch1 { { "a", json::value() }, { "b", json::value() } };
	json::wobject ch2 { { L"a", json::value() }, { L"b", json::value() } };

	assert(obj1 == ch1);
	assert(obj2 == ch2);
}

void check_redundant()
{
	const string str1 = "   {\n\t\"a\"\n\n\t\r:   null \n\n\r  ,\n\t\"a\"\n\n\t\r:   {   } \n\n,\r \"b\": \t\tnull}\r\n  ";
	const wstring str2 = L"{  \r\t \"a\"\n\n\t\r:   null  \n\n\r  ,\n\t\"a\"\n\n\t\r:   {   } \n\n,\r\"b\": \r\tnull }\n\t  \n  \n\r  ";

	istringstream is1(str1);
	json::value v1;
	is1 >> v1;

	wistringstream is2(str2);
	json::value v2;
	is2 >> v2;

	const json::object& obj1(v1);
	const json::wobject& obj2(v2);
	json::object ch1 { { "a", json::value() }, { "b", json::value() } };
	json::wobject ch2 { { L"a", json::value() }, { L"b", json::value() } };

	assert(obj1 == ch1);
	assert(obj2 == ch2);
}

int main(int, char**)
{
	check_empty();
	check_one();
	check_two();
	check_redundant();

	return 0;
}
