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
#include <cmath>
#include <limits>

#include "peli/json/value.h"

using namespace std;

using namespace peli;

void check_zero()
{
	const string str1 = "[0]";
	const wstring str2 = L"[0]";

	ostringstream os1;
	wostringstream os2;

	json::array ch1 { json::number { } };
	json::value v1(ch1);

	os1 << v1;
	os2 << v1;

	assert(os1.str() == str1);
	assert(os2.str() == str2);
}

void check_integer()
{
	const string str1 = "[-123456,123456]";
	const wstring str2 = L"[-123456,123456]";

	ostringstream os1;
	wostringstream os2;

	json::array ch1 { json::number { -123456 }, json::number { 123456 } };
	json::value v1(ch1);

	os1 << v1;
	os2 << v1;

	assert(os1.str() == str1);
	assert(os2.str() == str2);
}

void check_decimal_fraction()
{
	const string str1 = "[3.4375,-3.4375,0.04,-0.04]";
	const wstring str2 = L"[3.4375,-3.4375,0.04,-0.04]";

	ostringstream os1;
	wostringstream os2;

	json::array ch1
	{
		json::number { 3.4375 },
		json::number { -3.4375 },
		json::value(json::number(0.04)),
		json::value(json::number(-0.04))
	};
	json::value v1(ch1);

	os1 << v1;
	os2 << v1;

	cout << "test:" << endl;
	cout << os1.str() << endl;
    std::cout << "The default precision is " << std::cout.precision() << '\n';
	assert(os1.str() == str1);
	assert(os2.str() == str2);
}

void check_engineer_fraction()
{
	const string str1 = "[3.4375,-3.4375,3.4375,-3.4375,0.04,-0.04]";
	const wstring str2 = L"[3.4375,-3.4375,3.4375,-3.4375,0.04,-0.04]";

	ostringstream os1;
	wostringstream os2;

	json::array ch1
	{
		json::number(0.34375e1),
		json::number(-0.34375e1),
		json::number(0.34375e1),
		json::number(-0.34375e1),
		json::number(4e-2),
		json::number(-4e-2)
	};
	json::value v1(ch1);

	os1 << v1;
	os2 << v1;

	cout << "test:" << endl;
	cout << os1.str() << endl;
    std::cout << "The default precision is " << std::cout.precision() << '\n';
	assert(os1.str() == str1);
	assert(os2.str() == str2);
}

int main(int, char**)
{
	check_zero();
	check_integer();
	check_decimal_fraction();
	check_engineer_fraction();

	return 0;
}
