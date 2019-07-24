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
