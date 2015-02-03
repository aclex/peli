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
	const string str1 = "   [\n\t\"\"   ]\r\n  ";
	const wstring str2 = L"[  \r\t\"\"   ]\n\t  \n  \n\r  ";

	istringstream is1(str1);
	json::value v1;
	is1 >> v1;

	wistringstream is2(str2);
	json::value v2;
	is2 >> v2;

	const json::array& arr1(v1);
	const json::array& arr2(v2);
	json::array ch1 { json::value("") };
	json::array ch2 { json::value(L"") };

	assert(arr1 == ch1);
	assert(arr2 == ch2);
}

void check_plain()
{
	const string str1 = "   [\n\t\"проверка обычной Unicode-строки\"   ]\r\n  ";
	const wstring str2 = L"[  \r\t\"проверка обычной Unicode-строки\"   ]\n\t  \n  \n\r  ";

	istringstream is1(str1);
	json::value v1;
	is1 >> v1;

	wistringstream is2(str2);
	json::value v2;
	is2 >> v2;

	const json::array& arr1(v1);
	const json::array& arr2(v2);
	json::array ch1 { json::value("проверка обычной Unicode-строки") };
	json::array ch2 { json::value(L"проверка обычной Unicode-строки") };

	assert(arr1 == ch1);
	assert(arr2 == ch2);
}

void check_verbal_escapes()
{
	const string str1 = "   [\n\t\"   check all the verbal escapes: \\\" \\\\ \\/ \\b \\f \\n \\r \\t \\\"\"   ]\r\n  ";
	const wstring str2 = L"[  \r\t\"   check all the verbal escapes: \\\" \\\\ \\/ \\b \\f \\n \\r \\t \\\"\"   ]\n\t  \n  \n\r  ";

	istringstream is1(str1);
	json::value v1;
	is1 >> v1;

	wistringstream is2(str2);
	json::value v2;
	is2 >> v2;

	const json::array& arr1(v1);
	const json::array& arr2(v2);
	const string& test_str(arr1[0]);
	json::array ch1 { json::value("   check all the verbal escapes: \" \\ / \b \f \n \r \t \"") };
	json::array ch2 { json::value(L"   check all the verbal escapes: \" \\ / \b \f \n \r \t \"") };

	assert(arr1 == ch1);
	assert(arr2 == ch2);
}

void check_u_escapes()
{
	const string str1 = "   [\n\t\"check unicode escapes: \\u043f\\u0440\\u0438\\u0432\\u0435\\u0442, \\u043C\\u0438\\u0440! \"   ]\r\n  ";
	const wstring str2 = L"[  \r\t\"check unicode escapes: \\u043f\\u0440\\u0438\\u0432\\u0435\\u0442, \\u043C\\u0438\\u0440!\"   ]\n\t  \n  \n\r  ";

	istringstream is1(str1);
	json::value v1;
	is1 >> v1;

	wistringstream is2(str2);
	json::value v2;
	is2 >> v2;

	const json::array& arr1(v1);
	const json::array& arr2(v2);
	json::array ch1 { json::value("check unicode escapes: привет, мир! ") };
	json::array ch2 { json::value(L"check unicode escapes: привет, мир! ") };

	assert(arr1 == ch1);
	assert(arr2 == ch2);
}

int main(int argc, char* argv[])
{
	check_empty();
	check_plain();
	check_verbal_escapes();
// 	check_u_escapes();

	return 0;
}
