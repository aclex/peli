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
	const string str1 = "   [\n\t0   ]\r\n  ";
	const wstring str2 = L"[  \r\t0   ]\n\t  \n  \n\r  ";

	istringstream is1(str1);
	json::value v1;
	is1 >> v1;

	wistringstream is2(str2);
	json::value v2;
	is2 >> v2;

	const json::array& arr1(v1);
	const json::array& arr2(v2);
	json::array ch1 { json::value(0) };

	assert(arr1 == ch1);
	assert(arr2 == ch1);
}

void check_integer()
{
	const string str1 = "   [\n\t-123456, 123456   ]\r\n  ";
	const wstring str2 = L"[  \r\t-123456, 123456   ]\n\t  \n  \n\r  ";

	istringstream is1(str1);
	json::value v1;
	is1 >> v1;

	wistringstream is2(str2);
	json::value v2;
	is2 >> v2;

	const json::array& arr1(v1);
	const json::array& arr2(v2);
	json::array ch1 { json::value(-123456), json::value(123456) };

	assert(arr1 == ch1);
	assert(arr2 == ch1);
}

void check_decimal_fraction()
{
	const string str1 = "   [\n\t3.4375, -3.4375, 0.04, -0.04   ]\r\n  ";
	const wstring str2 = L"[  \r\t3.4375, -3.4375, 0.04, -0.04   ]\n\t  \n  \n\r  ";

	istringstream is1(str1);
	json::value v1;
	is1 >> v1;

	wistringstream is2(str2);
	json::value v2;
	is2 >> v2;

	const json::array& arr1(v1);
	const json::array& arr2(v2);
	json::array ch1
	{
		json::value(3.4375),
		json::value(-3.4375),
		json::value(json::number(0.04)),
		json::value(json::number(-0.04))
	};

	json::number precision = pow(10, -1 * (numeric_limits<json::number>::digits10 - 1));

	if (fabs(static_cast<json::number>(arr1[2]) - static_cast<json::number>(ch1[2])) < precision)
		ch1[2] = arr1[2];

	if (fabs(static_cast<json::number>(arr1[3]) - static_cast<json::number>(ch1[3])) < precision)
		ch1[3] = arr1[3];

	assert(arr1 == ch1);
	assert(arr2 == ch1);
}

void check_engineer_fraction()
{
	const string str1 = "   [\n\t0.34375e1, -0.34375e+1, 0.34375E1, -0.34375E+1, 4e-2, -4e-2   ]\r\n  ";
	const wstring str2 = L"[  \r\t0.34375e1, -0.34375e+1, 0.34375E1, -0.34375E+1, 4e-2, -4e-2   ]\n\t  \n  \n\r  ";

	istringstream is1(str1);
	json::value v1;
	is1 >> v1;

	wistringstream is2(str2);
	json::value v2;
	is2 >> v2;

	const json::array& arr1(v1);
	const json::array& arr2(v2);
	json::array ch1
	{
		json::value(3.4375),
		json::value(-3.4375),
		json::value(3.4375),
		json::value(-3.4375),
		json::value(json::number(4e-2)),
		json::value(json::number(-4e-2))
	};

	json::number precision = pow(10, -1 * (numeric_limits<json::number>::digits10 - 1));

	if (fabs(static_cast<json::number>(arr1[4]) - static_cast<json::number>(ch1[4])) < precision)
		ch1[4] = arr1[4];

	if (fabs(static_cast<json::number>(arr1[5]) - static_cast<json::number>(ch1[5])) < precision)
		ch1[5] = arr1[5];

	assert(arr1 == ch1);
	assert(arr2 == ch1);
}

int main(int argc, char* argv[])
{
	check_zero();
	check_integer();
	check_decimal_fraction();
	check_engineer_fraction();

	return 0;
}
