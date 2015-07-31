#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#include <cstring>

#include "io_utils.h"
using namespace std;
using namespace std::chrono;

static const size_t MAX_BLOCKSIZE = 20l*1024l*1024l*1024l/sizeof(short);
void write_data(size_t size, const string & filename) {
	//use maximum 20 GB
	size_t nb_blocks = size/MAX_BLOCKSIZE+1;
	size_t block_size = size/nb_blocks;
	short * rnd_data = new short[block_size];
	double duration_s = 0;
	ofstream os;
	os.open(filename, ios::out | ios::binary);
	for (size_t b=0; b<nb_blocks; b++)
	{
		for (size_t i=0; i<block_size; i++)
			rnd_data[i] = rand()%100;

		auto start = steady_clock::now();
		os.write( (char*) rnd_data, block_size*sizeof(short));
		auto end = steady_clock::now();
		duration_s += duration<double>(end-start).count();
	}
	os.close();
	cout << "Operation \"writing data\" took " << duration_s << " seconds" << endl;
	output_average_speed(filename,duration_s);
	delete[] rnd_data;
}
void read_data(size_t size, const string & filename) {
	size_t nb_blocks = size/MAX_BLOCKSIZE+1;
	size_t block_size = size/nb_blocks;
	short * data = new short[block_size];
	ifstream is;
	is.open(filename, ios::in | ios::binary);
	auto start = steady_clock::now();
	for (size_t b=0; b<nb_blocks; b++)
		is.read( (char*) data, block_size*sizeof(short));
	auto end = steady_clock::now();
	is.close();
	double duration_s = duration<double>(end-start).count();
	cout << "Operation \"reading data\" took " << duration_s << " seconds" << endl;
	output_average_speed(filename,duration_s);
	delete[] data;
}


