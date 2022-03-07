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
#include <cmath>
#include <limits>

#include "peli/json/value.h"

#include "exception_check.h"

using namespace std;

using namespace peli;
using namespace peli::test;

int check_zero()
{
	const string str1 = "   [\n\t0   ]\r\n  ";
	const wstring str2 = L"[  \r\t0   ]\n\t  \n  \n\r  ";

	istringstream is1(str1);
	json::value v1;
	is1 >> v1;

	wistringstream is2(str2);
	json::wvalue v2;
	is2 >> v2;

	const json::array& arr1(get<json::array>(v1));
	const json::warray& arr2(get<json::warray>(v2));
	json::array ch1 { json::number(0) };
	json::warray ch2 { json::number(0) };

	if (arr1 != ch1)
		return 1;

	if (arr2 != ch2)
		return 2;

	return 0;
}

int check_integer()
{
	const string str1 = "   [\n\t-123456, 123456   ]\r\n  ";
	const wstring str2 = L"[  \r\t-123456, 123456   ]\n\t  \n  \n\r  ";

	istringstream is1(str1);
	json::value v1;
	is1 >> v1;

	wistringstream is2(str2);
	json::wvalue v2;
	is2 >> v2;

	const json::array& arr1(get<json::array>(v1));
	const json::warray& arr2(get<json::warray>(v2));
	json::array ch1 { json::number { -123456 }, json::number { 123456 } };
	json::warray ch2 { json::number { -123456 }, json::number { 123456 } };

	if (arr1 != ch1)
		return 3;

	if (arr2 != ch2)
		return 4;

	return 0;
}

int check_decimal_fraction()
{
	const string str1 = "   [\n\t3.4375, -3.4375, 0.04, -0.04   ]\r\n  ";
	const wstring str2 = L"[  \r\t3.4375, -3.4375, 0.04, -0.04   ]\n\t  \n  \n\r  ";

	istringstream is1(str1);
	json::value v1;
	is1 >> v1;

	wistringstream is2(str2);
	json::wvalue v2;
	is2 >> v2;

	const json::array& arr1(get<json::array>(v1));
	const json::warray& arr2(get<json::warray>(v2));
	json::array ch1
	{
		json::number(3.4375),
		json::number(-3.4375),
		json::value(json::number(0.04)),
		json::value(json::number(-0.04))
	};

	json::warray ch2
	{
		json::number(3.4375),
		json::number(-3.4375),
		json::wvalue(json::number(0.04)),
		json::wvalue(json::number(-0.04))
	};

	json::number precision = pow(10, -1 * (numeric_limits<json::number>::digits10 - 2));

	if (abs(get<json::number>(arr1[2]) - get<json::number>(ch1[2])) < precision)
		ch1[2] = arr1[2];

	if (abs(get<json::number>(arr1[3]) - get<json::number>(ch1[3])) < precision)
		ch1[3] = arr1[3];

	if (arr1 != ch1)
		return 5;

	if (arr2 != ch2)
		return 6;

	return 0;
}

int check_engineer_fraction()
{
	const string str1 = "   [\n\t0.34375e1, -0.34375e+1, 0.34375E1, -0.34375E+1, 4e-2, -4e-2   ]\r\n  ";
	const wstring str2 = L"[  \r\t0.34375e1, -0.34375e+1, 0.34375E1, -0.34375E+1, 4e-2, -4e-2   ]\n\t  \n  \n\r  ";

	istringstream is1(str1);
	json::value v1;
	is1 >> v1;

	wistringstream is2(str2);
	json::wvalue v2;
	is2 >> v2;

	const json::array& arr1(get<json::array>(v1));
	const json::warray& arr2(get<json::warray>(v2));
	json::array ch1
	{
		json::number { 3.4375 },
		json::number { -3.4375 },
		json::number { 3.4375 },
		json::number { -3.4375 },
		json::value(json::number(4e-2)),
		json::value(json::number(-4e-2))
	};

	json::warray ch2
	{
		json::number { 3.4375 },
		json::number { -3.4375 },
		json::number { 3.4375 },
		json::number { -3.4375 },
		json::wvalue(json::number(4e-2)),
		json::wvalue(json::number(-4e-2))
	};

	json::number precision = pow(10, -1 * (numeric_limits<json::number>::digits10 - 2));

	if (fabs(get<json::number>(arr1[4]) - get<json::number>(ch1[4])) < precision)
		ch1[4] = arr1[4];

	if (fabs(get<json::number>(arr1[5]) - get<json::number>(ch1[5])) < precision)
		ch1[5] = arr1[5];

	if (arr1 != ch1)
		return 7;

	if (arr2 != ch2)
		return 8;

	return 0;
}

int check_overflow()
{
#ifdef USE_FLOAXIE
	if (!has_thrown_on<parse_error>("[45e+1459823]"))
		return 9;
#endif

	return 0;
}

int check_long_enough()
{
	if (has_thrown_on<parse_error>("[1.0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123, 23]"))
		return 10;

	return 0;
}

int check_longer()
{
	if (!has_thrown_on<parse_error>("[1.01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789, 23]"))
		return 11;

	return 0;
}

int main(int, char**)
{
	if (const auto r = check_zero())
		return r;

	if (const auto r = check_integer())
		return r;

	if (const auto r = check_decimal_fraction())
		return r;

	if (const auto r = check_engineer_fraction())
		return r;

	if (const auto r = check_overflow())
		return r;

	if (const auto r = check_long_enough())
		return r;

	if (const auto r = check_longer())
		return r;

	return 0;
}
