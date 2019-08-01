Peli
======
[![Build Status in GCC/Clang](https://travis-ci.org/aclex/peli.svg?branch=master)](https://travis-ci.org/aclex/peli) [![Build status in Visual Studio](https://ci.appveyor.com/api/projects/status/2d028d4f4lt67ejr?svg=true)](https://ci.appveyor.com/project/aclex/peli) [![Code coverage](https://codecov.io/gh/aclex/peli/branch/master/graph/badge.svg)](https://codecov.io/gh/aclex/peli)

Peli is C++14/C++17 header-only library for parsing and printing files in [JSON](https://json.org/) format.

Why yet another JSON library, please?
-------------------------------------

Oh yes, indeed… In short, for two reasons: first class performance and modern C++ interface and use idioms. With no need to choose only one of the two.

But why 'peli'?
---------------
After [Pelias](https://en.wikipedia.org/wiki/Pelias). As Wiki reads: "He was the one who sent Jason on the quest for the Golden Fleece.", while the JSON to "Jason" allegory can often be seen both in pronunciation and in the related projects titles.

What is it for?
---------------

The aim is general purpose, yet fast, library for loading, processing and saving JSON files utilizing modern C++ facilities to avoid performance and programming overhead preserving simple and consise API. `std::variant` in the latest C++17 standard also helps a lot to keep things simple and consistent.

Here're the general goals of the project:
- API as simple and short, as possible, based on native C++ and Standard Library types and idioms
- robust and correct [ECMA-404](http://www.ecma-international.org/publications/files/ECMA-ST/ECMA-404.pdf)-compliant implementation without ghosts under the hood
- comparable performance among the top-speed JSON libraries out there
- easy to use in the project (hence, header-only format is preferred)

Features
--------
1. Per-format `basic_value<>` type to store values of all possible entities. It's literally a specialization of either `std::variant` (with C++17 on) or internal variant implementation (for C++14) (in fact it's derived without data members added to allow recurrent use). Variant's very own functions like `get()` or `visit()` is there for your accessing pleasure, too.
2. [`floaxie`](https://github.com/aclex/floaxie)-driven number parsing and printing for maximum speed.
3. Template-based parsing and printing code for better inlining and compile-time calculations.
4. Dense test coverage to improve correctness and stability in most possible set of use cases.

Compiler compatibility
----------------------
### Default `std::variant`-based implementation
- [x] GCC 7
- [x] Clang 4
- [x] Visual Studio 2017 15.0

### Fallback internal variant-based implementation
- [x] GCC 5
- [x] Clang 3.6
- [x] Visual Studio 2017 15.0

Example
-------
```cpp
#include <iostream>
#include <fstream>

#include "peli/json/value.h"
#include "peli/json/iomanip.h"

using namespace std;
using namespace peli;

int main(int, char**)
{
	ifstream input_file("input.json");

	// load from input file stream
	json::value v;
	input_file >> v;

	if (!input_file.good())
	{
		cerr << "Input file is not correct JSON file." << endl;
		return 1;
	}

	// list all keys in root element, assuming root is object
	cout << "Root keys:" << endl;
	for (const auto& p : get<json::object>(v))
	{
		cout << p.first << '\n';
	}

	// add another integer element to root object
	get<json::object>(v)["addme"] = json::number { 42 };

	ofstream output_file("output.json");
	// save to output file stream
	output_file << json::pretty << v;

	if (!output_file.good())
	{
		cerr << "Unable to save to output file." << endl;
		return 2;
	}
}
```

Including to CMake project as a subproject
-------
Peli can be included in any CMake project as a subproject fairly easily thanks to modern CMake `INTERFACE_LIBRARY` target facilities. Unfortunately, this works fully since CMake 3.13 (no way to use targets out of directory scope before this version, which makes the whole deal pretty useless).

`CMakeLists.txt` of a consumer CMake project would look like this (given Peli is cloned to `peli` subdirectory)':
```cmake
project(foo)

cmake_minimum_required(VERSION 3.13)

# `EXCLUDE_FOR_ALL` here to exclude supplementary targets
# like `install` from the main project target set
add_subdirectory(peli EXCLUDE_FROM_ALL) 

add_executable(foo_main foo_main.cpp)
target_link_libraries(foo_main PUBLIC peli)
```
