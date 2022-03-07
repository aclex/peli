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

bool check_zero()
{
#ifdef USE_FLOAXIE
	const string str1 = "[0]";
	const wstring str2 = L"[0]";
#else
	const string str1 = "[0.000000]";
	const wstring str2 = L"[0.000000]";
#endif

	ostringstream os1;
	wostringstream os2;

	json::array ch1 { json::number { } };
	json::value v1(ch1);
	json::warray ch2 { json::number { } };
	json::wvalue v2(ch2);

	os1 << v1;
	os2 << v2;

	const auto& s{os1.str()};
	if (os1.str() != str1)
		return false;

	if (os2.str() != str2)
		return false;

	return true;
}

bool check_nan()
{
	json::array ch { json::number {NAN} };
	json::value v(ch);

	return test::has_thrown_on<invalid_argument>(v);
}

bool check_inf()
{
	json::array ch { json::number {INFINITY} };
	json::value v(ch);

	return test::has_thrown_on<invalid_argument>(v);
}

bool check_integer()
{
#ifdef USE_FLOAXIE
	const string str1 = "[-123456,123456]";
	const wstring str2 = L"[-123456,123456]";
#else
	const string str1 = "[-123456.000000,123456.000000]";
	const wstring str2 = L"[-123456.000000,123456.000000]";
#endif

	ostringstream os1;
	wostringstream os2;

	json::array ch1 { json::number { -123456 }, json::number { 123456 } };
	json::value v1(ch1);
	json::warray ch2 { json::number { -123456 }, json::number { 123456 } };
	json::wvalue v2(ch2);

	os1 << v1;
	os2 << v2;

	const auto& s{os1.str()};
	if (os1.str() != str1)
		return false;
	if (os2.str() != str2)
		return false;

	return true;
}

bool check_decimal_fraction()
{
#ifdef USE_FLOAXIE
	const string str1 = "[3.4375,-3.4375,0.04,-0.04]";
	const wstring str2 = L"[3.4375,-3.4375,0.04,-0.04]";
#else
	const string str1 = "[3.437500,-3.437500,0.040000,-0.040000]";
	const wstring str2 = L"[3.437500,-3.437500,0.040000,-0.040000]";
#endif

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

	json::warray ch2
	{
		json::number { 3.4375 },
		json::number { -3.4375 },
		json::wvalue(json::number(0.04)),
		json::wvalue(json::number(-0.04))
	};
	json::wvalue v2(ch2);

	os1 << v1;
	os2 << v2;

	cout << "test:" << endl;
	cout << os1.str() << endl;
    std::cout << "The default precision is " << std::cout.precision() << '\n';
	if (os1.str() != str1)
		return false;

	if (os2.str() != str2)
		return false;

	return true;
}

bool check_engineer_fraction()
{
#ifdef USE_FLOAXIE
	const string str1 = "[3.4375,-3.4375,3.4375,-3.4375,0.04,-0.04]";
	const wstring str2 = L"[3.4375,-3.4375,3.4375,-3.4375,0.04,-0.04]";
#else
	const string str1 = "[3.437500,-3.437500,3.437500,-3.437500,0.040000,-0.040000]";
	const wstring str2 = L"[3.437500,-3.437500,3.437500,-3.437500,0.040000,-0.040000]";
#endif

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

	json::warray ch2
	{
		json::number(0.34375e1),
		json::number(-0.34375e1),
		json::number(0.34375e1),
		json::number(-0.34375e1),
		json::number(4e-2),
		json::number(-4e-2)
	};
	json::wvalue v2(ch2);

	os1 << v1;
	os2 << v2;

	cout << "test:" << endl;
	cout << os1.str() << endl;
    std::cout << "The default precision is " << std::cout.precision() << '\n';
	if (os1.str() != str1)
		return false;

	if (os2.str() != str2)
		return false;

	return true;
}

int main(int, char**)
{
	if (!check_zero())
		return 1;

	if (!check_integer())
		return 2;

	if (!check_decimal_fraction())
		return 3;

	if (!check_engineer_fraction())
		return 4;

	if (!check_nan())
		return 5;

	if (!check_inf())
		return 6;

	return 0;
}
