#include <iostream>
#include <cstdlib>
#include <chrono>
#include "matmul_utils.h"
using namespace std;
using namespace std::chrono;

int main()
{
	SIZE=1500;
	double ** A, ** B, ** C, ** C_ref;
	new_mat(A); 
	new_mat(B); 
	new_mat(C); 
	new_mat(C_ref);
	init_mat_rand(A); 
	init_mat_rand(B); 
	init_mat_zero(C); 
	init_mat_zero(C_ref);
	
	auto start = steady_clock::now();
	MATMUL(A,B,C);
	matmul_mkl(A,B,C_ref);
	std::cout << "Distance between C and C_ref:" << compare(C,C_ref) << std::endl;
	auto end = steady_clock::now();
	cout << "Operation \"Validation\" took " << duration<double>(end-start).count() << " seconds" << endl;

	delete_mat(A); 
	delete_mat(B); 
	delete_mat(C); 
	delete_mat(C_ref);
}

