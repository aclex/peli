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

#include "peli/json/value.h"
#include "peli/json/find.h"

using namespace std;

using namespace peli;

namespace
{
	const string example
	{
		"{"
			"\"foo\": [\"bar\", \"baz\"],"
			"\"\": 0,"
			"\"a/b\": 1,"
			"\"c%d\": 2,"
			"\"e^f\": 3,"
			"\"g|h\": 4,"
			"\"i\\\\j\": 5,"
			"\"k\\\"l\": 6,"
			"\" \": 7,"
			"\"m~n\": 8"
		"}"
	};
}

bool check_empty()
{
	auto v { json::value::parse(example) };

	auto s { json::find(v, ""s) };

	if (!s)
		return false;

	if (s != &v)
		return false;

	cout << "check_empty: " << *s << endl;

	return true;
}

bool check_slash()
{
	auto v { json::value::parse(example) };

	auto s { json::find(v, "/"s) };

	if (!s)
		return false;

	const auto& obj{get<json::object>(v)};
	const auto& expected{obj.at("")};

	cout << "check_slash: " << *s << endl;

	if (s != &expected)
		return false;

	return true;
}

bool check_foo()
{
	auto v { json::value::parse(example) };

	auto s { json::find(v, "/foo"s) };

	if (!s)
		return false;

	cout << "check_foo: " << *s << endl;

	const auto& obj{get<json::object>(v)};
	const auto& expected{obj.at("foo")};

	if (s != &expected)
		return false;

	return true;
}

bool check_foo_0()
{
	auto v { json::value::parse(example) };

	auto s { json::find(v, "/foo/0"s) };

	if (!s)
		return false;

	cout << "check_foo_0: " << *s << endl;

	const auto& obj{get<json::object>(v)};
	const auto& foo{get<json::array>(obj.at("foo"))};
	const auto& expected{foo[0]};

	if (s != &expected)
		return false;

	return true;
}

bool check_a_slash_b()
{
	auto v { json::value::parse(example) };

	auto s { json::find(v, "/a~1b"s) };

	if (!s)
		return false;

	cout << "check_a_slash_b: " << *s << endl;

	const auto& obj{get<json::object>(v)};
	const auto& expected{obj.at("a/b")};

	if (s != &expected)
		return false;

	return true;
}

bool check_c_percent_d()
{
	auto v { json::value::parse(example) };

	auto s { json::find(v, "/c%d"s) };

	if (!s)
		return false;

	cout << "check_c_percent_d: " << *s << endl;

	const auto& obj{get<json::object>(v)};
	const auto& expected{obj.at("c%d")};

	if (s != &expected)
		return false;

	return true;
}

bool check_e_circum_f()
{
	auto v { json::value::parse(example) };

	auto s { json::find(v, "/e^f"s) };

	if (!s)
		return false;

	cout << "check_e_circum_f: " << *s << endl;

	const auto& obj{get<json::object>(v)};
	const auto& expected{obj.at("e^f")};

	if (s != &expected)
		return false;

	return true;
}

bool check_g_pipe_h()
{
	auto v { json::value::parse(example) };

	auto s { json::find(v, "/g|h"s) };

	if (!s)
		return false;

	cout << "check_g_pipe_h: " << *s << endl;

	const auto& obj{get<json::object>(v)};
	const auto& expected{obj.at("g|h")};

	if (s != &expected)
		return false;

	return true;
}

bool check_i_double_bslash_j()
{
	auto v { json::value::parse(example) };

	auto s { json::find(v, string{"/i\\j"}) };

	if (!s)
		return false;

	cout << "check_i_double_bslash_j: " << *s << endl;

	const auto& obj{get<json::object>(v)};
	const auto& expected{obj.at("i\\j")};

	if (s != &expected)
		return false;

	return true;
}

bool check_k_quote_l()
{
	auto v { json::value::parse(example) };

	auto s { json::find(v, "/k\"l"s) };

	if (!s)
		return false;

	cout << "check_k_quote_l: " << *s << endl;

	const auto& obj{get<json::object>(v)};
	const auto& expected{obj.at("k\"l")};

	if (s != &expected)
		return false;

	return true;
}

bool check_space()
{
	auto v { json::value::parse(example) };

	auto s { json::find(v, "/ "s) };

	if (!s)
		return false;

	cout << "check_space: " << *s << endl;

	const auto& obj{get<json::object>(v)};
	const auto& expected{obj.at(" ")};

	if (s != &expected)
		return false;

	return true;
}

bool check_m_tilda_n()
{
	auto v { json::value::parse(example) };

	auto s { json::find(v, "/m~0n"s) };

	if (!s)
		return false;

	cout << "check_m_tilda_n: " << *s << endl;

	const auto& obj{get<json::object>(v)};
	const auto& expected{obj.at("m~n")};

	if (s != &expected)
		return false;

	return true;
}

bool check_converting()
{
	auto v { json::value::parse(example) };

	auto s { json::find_of<json::array>(v, "/foo"s) };

	if (!s)
		return false;

	cout << "check_foo: " << json::value{*s} << endl;

	const auto& obj{get<json::object>(v)};
	auto* const expected{get_if<json::array>(&obj.at("foo"))};

	if (s != expected)
		return false;

	return true;
}

int main(int, char**)
{
	if (!check_empty())
		return 1;

	if (!check_slash())
		return 2;

	if (!check_foo())
		return 3;

	if (!check_foo_0())
		return 4;

	if (!check_a_slash_b())
		return 5;

	if (!check_c_percent_d())
		return 6;

	if (!check_e_circum_f())
		return 7;

	if (!check_g_pipe_h())
		return 8;

	if (!check_i_double_bslash_j())
		return 9;

	if (!check_k_quote_l())
		return 10;

	if (!check_space())
		return 11;

	if (!check_m_tilda_n())
		return 12;

	if (!check_converting())
		return 13;

	return 0;
}
