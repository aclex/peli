Peli
======
[![Build Status in GCC/Clang](https://travis-ci.org/aclex/peli.svg?branch=master)](https://travis-ci.org/aclex/peli) [![Build status in Visual Studio](https://ci.appveyor.com/api/projects/status/nhidn1n2o66etirk?svg=true)](https://ci.appveyor.com/project/aclex/peli) [![Code coverage](https://codecov.io/gh/aclex/peli/branch/master/graph/badge.svg)](https://codecov.io/gh/aclex/peli)

Peli is C++14/C++17 header-only library for parsing and printing files in [JSON](https://json.org/) format. It tries to use `std::variant`, if ever possible (i.e. when being built with C++17-enabled compiler), but can use internal variant type implementation otherwise.

What is it for?
---------------

The main aim of writing yet another JSON interation library is to have general purpose, yet fast, library for loading, processing and saving JSON files utilizing modern C++ facilities to avoid excessive overhead preserving simple and consise API. Appearance of `std::variant` in latest C++17 standard also allows keeping the codebase minimal.

General goals of the project are:
- API as simple and short, as possible, based on native C++ and Standard Library types and idioms
- robust and correct [ECMA-404](http://www.ecma-international.org/publications/files/ECMA-ST/ECMA-404.pdf)-compliant neat implementation without ghosts under the hood
- fast, as much, as possible, operations, with no sacrifice on API side

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
	for (const auto& p : static_cast<json::object&>(v))
	{
		cout << p.first << '\n';
	}

	// add another integer element to root object
	static_cast<json::object&>(v)["addme"] = json::value(42);

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

add_subdirectory(peli)

add_executable(foo_main foo_main.cpp)
target_link_libraries(foo_main PUBLIC peli)
```
