#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "mpi.h"

/*
 * Generate a random point in the square, then test and return whether it is
 * inside the circle.
 */ 
bool generate_point()
{
	double x; // X coordinate of point inside the square
	double y; // Y coordinate of point inside the square
	x = (double) rand() / RAND_MAX;
	y = (double) rand() / RAND_MAX;
	return (sqrt(x * x + y * y) <= 1.0);
}

/*
 * Estimate Pi over MPI using a Monte Carlo algorithm, printing an estimate
 * after each iteration
 *
 *     n:    Number of random points to test (the higher, the more precise the
 *           estimate will be)
 *     comm: MPI communicator
 */
void pi_monte_carlo(int n, MPI_Comm comm)
{
	int rank; // Rank inside the MPI communicator
	int size; // Size of the MPI communicator
	int pw;   // 0 or 1, was the point inside the circle for this rank and this
	          // iteration?
	int pc;   // Number of points inside the circle, summed for all ranks for
	          // this cycle of iteration
	int p;     // Total number of points inside the circle (pi = 4*p/n)
	int m;     // Number of points tested up to now
	double pi; // Pi estimate

	/* Initialize variables and check that the number of points is valid.
	 * We simplify the algorithm by forcing n to be a multiple of the number
	 * of processes.
	 */
	MPI_Comm_rank(comm, &rank);
	MPI_Comm_size(comm, &size);
	p = 0;
	if (n % size != 0)
	{
		if (rank == 0)
		{
			printf("Invalid number of points: %d\n", n);
			printf("Must be a multiple of: %d\n", size);
		}
		return;
	}

	// Compute pi
	for (m = size; m <= n; m += size)
	{
		pw = (int) generate_point();
		MPI_Reduce(&pw, &pc, 1, MPI_INT, MPI_SUM, 0, comm);
		// Rank 0 prints the estimate
		if (rank == 0)
		{
			p += pc;
			pi = (double) 4 * p / m;
			if (m % (n/10) == 0) printf("%d %.20f\n", m, pi);
		}
	}
}

int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	pi_monte_carlo(atoi(argv[1]), MPI_COMM_WORLD);
	MPI_Finalize();
	return 0;
}
