#include <iostream>
#include <cstdlib>
#include <chrono>
#include "omp.h"
#include "matmul_utils.h"
using namespace std;
using namespace std::chrono;

int main()
{
	double ** A, ** B, ** C;
	new_mat(A); 
	new_mat(B); 
	new_mat(C); 
	init_mat_rand(A); 
	init_mat_rand(B); 
	init_mat_zero(C); 
	
	auto start = steady_clock::now();
	omp_set_num_threads(1);
	MATMUL(A,B,C);
	auto end = steady_clock::now();
	double duration_single_thread = duration<double>(end-start).count();
	cout << "Single-threaded duration: " << duration_single_thread << " seconds" << endl;
	int nrepeat = 1;
	if (duration_single_thread < 60)
	{
		nrepeat = (int)(60/duration_single_thread);
		cout << "Warning: Single-threaded duration too short to get a scaling. Repeating " << nrepeat << " times." << endl;
	}

	start = steady_clock::now();
	omp_set_num_threads(1);
	for (int i=0; i<nrepeat; i++)
		MATMUL(A,B,C);
	end = steady_clock::now();
	duration_single_thread = duration<double>(end-start).count();
	cout << "Single-threaded duration: " << duration_single_thread << " seconds" << endl;

	start = steady_clock::now();
	omp_set_num_threads(8);
	for (int i=0; i<nrepeat; i++)
		MATMUL(A,B,C);
	end = steady_clock::now();
	double duration_multi_thread = duration<double>(end-start).count();
	cout << "8-threaded duration: " << duration_multi_thread << " seconds" << endl;
	cout << "Efficiency: " << duration_single_thread/(8*duration_multi_thread)*100 << "%" << endl;

	
	delete_mat(A); 
	delete_mat(B); 
	delete_mat(C); 
}

