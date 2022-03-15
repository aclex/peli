#include <iostream>
#include <fstream>

#include "peli/json/value.h"
#include "peli/json/iomanip.h"
#include "peli/json/find.h"

using namespace std;
using namespace peli;

int main(int, char**)
{
	ifstream input_file("input.json");

	if (!input_file)
	{
		cerr << "Can't open input file." << endl;
		return 1;
	}

	// load from input file stream
	json::value v;
	input_file >> v;

	if (!input_file.good())
	{
		cerr << "Input file is not correct JSON file." << endl;
		return 2;
	}

	// list all keys in root element, assuming root is object
	cout << "Root keys:" << endl;
	for (const auto& p : get<json::object>(v))
	{
		cout << p.first << '\n';
	}

	auto inl { json::value::parse("[\"I'm parsed inline\"]"s) };
	get<json::object>(v)["inline"] = inl;

	auto* const p { json::find_of<bool>(v, "/three"s) };

	if (p)
		*p = true;

	// add another integer element to root object
	get<json::object>(v)["addme"] = json::number { 42 };

	const auto& dump { json::to_string(v, /*pretty*/ true) };

	cout << "Content of the result:" << endl;
	cout << dump << endl;

	ofstream output_file("output.json");
	// save to output file stream
	output_file << json::pretty << v;

	if (!output_file.good())
	{
		cerr << "Unable to save to output file." << endl;
		return 3;
	}
}
