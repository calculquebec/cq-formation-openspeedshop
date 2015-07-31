#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>

#include "io_utils.h"
using namespace std;
using namespace std::chrono;

void write_data(size_t size, const string & filename) {
	ofstream os;
	os.open(filename, ios::out | ios::binary);
	int rnd_datum;
	auto start = steady_clock::now();
	for (size_t i=0; i<size; i++)
	{
		rnd_datum = rand()%100;
		os.write( (char*) &rnd_datum, sizeof(int));
	}
	os.close();
	auto end = steady_clock::now();
	double duration_s = duration<double>(end-start).count();
	cout << "Operation \"writing data\" took " << duration_s << " seconds" << endl;
	output_average_speed(filename,duration_s);
}
void read_data(size_t size, const string & filename) {
	ifstream is;
	is.open(filename, ios::in | ios::binary);
	int datum;
	auto start = steady_clock::now();
	for (size_t i=0; i<size; i++)
	{
		is.read( (char*) &datum, sizeof(int));
	}
	auto end = steady_clock::now();
	double duration_s = duration<double>(end-start).count();
	cout << "Operation \"reading data\" took " << duration_s << " seconds" << endl;
	output_average_speed(filename,duration_s);
	is.close();
}


