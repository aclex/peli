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

#include <cstdlib>

#include "peli/json/value.h"

using namespace std;

using namespace peli;

int check_empty()
{
	const string str1 = "   [\n\t\"\"   ]\r\n  ";
	const wstring str2 = L"[  \r\t\"\"   ]\n\t  \n  \n\r  ";

	istringstream is1(str1);
	json::value v1;
	is1 >> v1;

	wistringstream is2(str2);
	json::wvalue v2;
	is2 >> v2;

	const json::array& arr1(get<json::array>(v1));
	const json::warray& arr2(get<json::warray>(v2));
	json::array ch1 { ""s };
	json::warray ch2 { L""s };

	if (arr1 != ch1)
		return 1;

	if (arr2 != ch2)
		return 2;

	return 0;
}

int check_plain()
{
	const string str1 = "   [\n\t\"проверка обычной Unicode-строки\"   ]\r\n  ";
	const wstring str2 = L"[  \r\t\"проверка обычной Unicode-строки\"   ]\n\t  \n  \n\r  ";

	istringstream is1(str1);
	json::value v1;
	is1 >> v1;

	wistringstream is2(str2);
	json::wvalue v2;
	is2 >> v2;

	const json::array& arr1(get<json::array>(v1));
	const json::warray& arr2(get<json::warray>(v2));
	json::array ch1 { "проверка обычной Unicode-строки"s };
	json::warray ch2 { L"проверка обычной Unicode-строки"s };

	if (arr1 != ch1)
		return 3;

	if (arr2 != ch2)
		return 4;

	return 0;
}

int check_verbal_escapes()
{
	const string str1 = "   [\n\t\"   check all the verbal escapes: \\\" \\\\ \\/ \\b \\f \\n \\r \\t \\\"\"   ]\r\n  ";
	const wstring str2 = L"[  \r\t\"   check all the verbal escapes: \\\" \\\\ \\/ \\b \\f \\n \\r \\t \\\"\"   ]\n\t  \n  \n\r  ";

	istringstream is1(str1);
	json::value v1;
	is1 >> v1;

	wistringstream is2(str2);
	json::wvalue v2;
	is2 >> v2;

	const json::array& arr1(get<json::array>(v1));
	const json::warray& arr2(get<json::warray>(v2));
	json::array ch1 { "   check all the verbal escapes: \" \\ / \b \f \n \r \t \""s };
	json::warray ch2 { L"   check all the verbal escapes: \" \\ / \b \f \n \r \t \""s };

	if (arr1 != ch1)
		return 5;

	if (arr2 != ch2)
		return 6;

	return 0;
}

int check_u_escapes()
{
	const string str1 = "   [\n\t\"check unicode escapes: \\u043f\\u0440\\u0438\\u0432\\u0435\\u0442, \\ud800\\udd75 \\ud834\\udd1e \\u043C\\u0438\\u0440! \"   ]\r\n  ";
	const wstring str2 = L"[  \r\t\"check unicode escapes: \\u043f\\u0440\\u0438\\u0432\\u0435\\u0442, \\ud800\\udd75 \\ud834\\udd1e \\u043C\\u0438\\u0440!\"   ]\n\t  \n  \n\r  ";

	istringstream is1(str1);
	json::value v1;
	is1 >> v1;

	wistringstream is2(str2);
	json::wvalue v2;
	is2 >> v2;

	const json::array& arr1(get<json::array>(v1));
	const json::warray& arr2(get<json::warray>(v2));
	json::array ch1 { "check unicode escapes: привет, 𐅵 𝄞 мир! "s };
	json::warray ch2 { L"check unicode escapes: привет, 𐅵 𝄞 мир!"s };

	if (arr1 != ch1)
		return 7;

	if (arr2 != ch2)
		return 8;

	return 0;
}

int main(int, char**)
{
	const int er = check_empty();

	if (er)
		return er;

	const int pr = check_plain();

	if (pr)
		return pr;

	const int vr = check_verbal_escapes();

	if (vr)
		return vr;

	const int ur = check_u_escapes();

	return ur;
}
