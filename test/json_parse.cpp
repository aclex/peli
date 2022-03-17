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

#include <cstdlib>

#include "peli/json/value.h"

#include "exception_check.h"

using namespace std;

using namespace peli;
using namespace peli::test;

int check_const_char()
{
	constexpr const char str1[] { "[\"test str1\"]" };
	constexpr const wchar_t str2[] { L"[\"test str2\"]" };

	json::array expected1 { "test str1"s };
	json::warray expected2 { L"test str2"s };

	const auto result1 { json::value::parse(str1) };
	const auto result2 { json::wvalue::parse(str2) };

	if (get<json::array>(result1) != expected1)
		return 1;

	if (get<json::warray>(result2) != expected2)
		return 2;

	return 0;
}

int check_string()
{
	const auto str1 { "[\"test str1\"]"s };
	const auto str2 { L"[\"test str2\"]"s };

	json::array expected1 { "test str1"s };
	json::warray expected2 { L"test str2"s };

	const auto result1 { json::value::parse(str1) };
	const auto result2 { json::wvalue::parse(str2) };

	if (get<json::array>(result1) != expected1)
		return 3;

	if (get<json::warray>(result2) != expected2)
		return 4;

	return 0;
}

#ifdef CXX_STD_17
int check_string_view()
{
	const auto str1 { "[\"test str1\"]"sv };
	const auto str2 { L"[\"test str2\"]"sv };

	json::array expected1 { "test str1"s };
	json::warray expected2 { L"test str2"s };

	const auto result1 { json::value::parse(str1) };
	const auto result2 { json::wvalue::parse(str2) };

	if (get<json::array>(result1) != expected1)
		return 5;

	if (get<json::warray>(result2) != expected2)
		return 6;

	return 0;
}
#endif

int main(int, char**)
{
	if (const auto r = check_const_char())
		return r;

	if (const auto r = check_string())
		return r;

#ifdef CXX_STD_17
	if (const auto r = check_string_view())
		return r;
#endif

	return 0;
}
