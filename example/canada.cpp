#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

#include "peli/json/value.h"

using namespace std;
using namespace peli;

int main(int argc, char* argv[])
{
	fstream f("canada.json", ios::in);
	f.sync_with_stdio(false);
	string str = string(istreambuf_iterator<char>(f), istreambuf_iterator<char>());
	istringstream ss(str);
	ss.sync_with_stdio(false);
	json::value v;

	auto start = chrono::high_resolution_clock::now();
	ss >> v;
	auto end = chrono::high_resolution_clock::now();

	cout << "loading canada.json taken " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us" << endl;

	return 0;
}

