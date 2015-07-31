#include <iostream>
#include <cstdlib>
using namespace std;

void new_mat(double ** & M)
{
	double * M_cont = new double[SIZE*SIZE];
	M = new double*[SIZE];
	for (int i=0; i<SIZE; i++)
		M[i] = &(M_cont[i*SIZE]);
}
void delete_mat(double ** & M)
{
	delete[] M[0];
	delete[] M;
}
void init_mat_rand(double ** M)
{
	for (int i=0; i<SIZE; i++)
		for (int j=0; j<SIZE; j++)
			M[i][j] = double(rand()%100);
}
void init_mat_zero(double ** M)
{
	for (int i=0; i<SIZE; i++)
		for (int j=0; j<SIZE; j++)
			M[i][j] = 0.;
}
void matmul2(double const * const * A, double const * const * B, double **C)
{
	#pragma omp parallel for collapse(2) default(none) shared(A,B,C)
	for (int i=0; i<SIZE; i++)
		for (int j=0; j<SIZE; j++)
			for (int k=0; k<SIZE; k++)
				C[i][k] += A[i][j]*B[j][k];
}

int main()
{
	double ** A, ** B, ** C;
	new_mat(A); 
	new_mat(B); 
	new_mat(C); 
	init_mat_rand(A); 
	init_mat_rand(B); 
	init_mat_zero(C); 
	
	for (int r=0; r<REPEAT; r++)
		matmul2(A,B,C);
	
	delete_mat(A); 
	delete_mat(B); 
	delete_mat(C); 
}

