#ifndef matmul_utils_h
#define matmul_utils_h
#include <cmath>
#include "mkl.h"
#ifdef CONTIGUOUS
	#define new_mat new_mat_cont
	#define delete_mat delete_mat_cont
#else
	#define new_mat new_mat_non_cont
	#define delete_mat delete_mat_non_cont
#endif

static int SIZE=500;
void new_mat_cont(double ** & M)
{
	double * M_cont = new double[SIZE*SIZE];
	M = new double*[SIZE];
	for (int i=0; i<SIZE; i++)
		M[i] = &(M_cont[i*SIZE]);
}
void new_mat_non_cont(double ** & M)
{
	M = new double * [SIZE];
	double ** trash = new double*[SIZE];
	for (int i=0; i<SIZE; i++) {
		M[i] = new double[SIZE];
		trash[i] = new double[8];
	}
	for (int i=0; i<SIZE; i++)
		delete[] trash[i];
	delete[] trash;
}
void delete_mat_cont(double ** & M)
{
	delete[] M[0];
	delete[] M;
}
void delete_mat_non_cont(double ** & M)
{
	for (int i=0; i<SIZE; i++)
		delete[] M[i];
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
double compare(double ** A, double ** B)
{
	double rel_error=0.;
	for (int i=0; i<SIZE; i++)
	{
		for (int j=0; j<SIZE; j++)
		{
			rel_error += 2*std::fabs(A[i][j]-B[i][j])/(std::fabs(A[i][j])+std::fabs(B[i][j]));
		}
	}
	return rel_error;
}

void matmul_mkl(double const * const * A, double const * const * B, double ** C)
{
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, SIZE, SIZE, SIZE, 1., A[0], SIZE, B[0], SIZE, 1., C[0], SIZE);
}
void matmul0(double const * const * A, double const * const * B, double **C)
{
	for (int i=0; i<SIZE; i++)
		for (int j=0; j<SIZE; j++)
			for (int k=0; k<SIZE; k++) 
				C[k][j] += A[k][i]*B[i][j];
}
void matmul1(double const * const * A, double const * const * B, double **C)
{
	for (int i=0; i<SIZE; i++)
		for (int j=0; j<SIZE; j++)
			for (int k=0; k<SIZE; k++)
				C[i][j] += A[i][k]*B[k][j];
}
void matmul1_omp(double const * const * A, double const * const * B, double **C)
{
	#pragma omp parallel for collapse(2) 
	for (int i=0; i<SIZE; i++)
		for (int j=0; j<SIZE; j++)
			for (int k=0; k<SIZE; k++)
				C[i][j] += A[i][k]*B[k][j];
}
void matmul2(double const * const * A, double const * const * B, double **C)
{
	#pragma omp parallel for collapse(1)
	for (int i=0; i<SIZE; i++)
		for (int j=0; j<SIZE; j++)
			for (int k=0; k<SIZE; k++)
				C[i][k] += A[i][j]*B[j][k];
}
void matmul_block(double const * const * A, double const * const * B, double **C)
{
	const int bs_L1=8*13;
    #pragma omp parallel for collapse(2) schedule(static,1) 
	for (int i1=0; i1<SIZE; i1+=bs_L1)
		for (int k1=0; k1<SIZE; k1+=bs_L1)
			for (int j1=0; j1<SIZE; j1+=bs_L1)
				for (int i=i1; i<std::min(i1+bs_L1,SIZE); i++)
					for (int j=j1; j<std::min(j1+bs_L1,SIZE); j++)
						for (int k=k1; k<std::min(k1+bs_L1,SIZE); k++)
							C[i][k] += A[i][j]*B[j][k];
}
#endif
