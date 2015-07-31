#include <iostream>
#include <cstdlib>
#include <chrono>
#include "matmul_utils.h"
using namespace std;
using namespace std::chrono;

int main(int argc, char * argv[])
{
	if (argc >= 2)
		SIZE=atoi(argv[1]);
	double ** A, ** B, ** C;
	new_mat(A); 
	new_mat(B); 
	new_mat(C); 
	init_mat_rand(A); 
	init_mat_rand(B); 
	init_mat_zero(C); 
	
	auto start = steady_clock::now();
	for (int r=0; r<REPEAT; r++)
		MATMUL(A,B,C);
	auto end = steady_clock::now();
	cout << "Operation \"Multiplications\" took " << duration<double>(end-start).count() << " seconds" << endl;
	
	delete_mat(A); 
	delete_mat(B); 
	delete_mat(C); 
}

