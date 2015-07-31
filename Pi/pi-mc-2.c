#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "mpi.h"

// Number of points to test at a time
#define np 10000

/*
 * Generate points inside the square and test if they are also inside the
 * circle. Then, return the number of points inside the circle.
 *
 *     n: Number of points to test
 */
int generate_points(int n)
{
	int i;
	int p = 0;
	double x;
	double y;
	for (i = 0; i < n; ++i)
	{
		x = (double) rand() / RAND_MAX;
		y = (double) rand() / RAND_MAX;
		if (sqrt(x * x + y * y) <= 1.0)
		{
			p++;
		}
	}
	return p;
}

/*
 * Estimate Pi over MPI using a Monte Carlo algorithm, printing an estimate
 * at regular intervals
 *
 *     n:    Number of random points to test (the higher, the more precise the
 *           estimate will be)
 *     comm: MPI communicator
 */
void pi_monte_carlo(long int n, MPI_Comm comm)
{
	int rank;   // Rank inside the MPI communicator
	int size;   // Size of the MPI communicator
	int pw;     // Number of points inside the circle for this rank and this
	            // estimate cycle
	int p;      // Total number of points inside the circle (pi = 4*p/n), summed
	            // for all ranks and estimate cycles
	int pc;     // Number of points inside the circle, summed for all ranks for
	            // this cycle of iteration
	long int m; // Number of points tested up to now
	double pi;  // Pi estimate

	/* Initialize variables and check that the number of points is valid.
	 * We simplify the algorithm by forcing n to be a multiple of the number
	 * of points per estimate cycle.
	 */
	MPI_Comm_rank(comm, &rank);
	MPI_Comm_size(comm, &size);
	p = 0;
	if (n % (size * np) != 0)
	{
		if (rank == 0)
		{
			printf("Invalid number of points: %ld\n", n);
			printf("Must be a multiple of: %d\n", size * np);
		}
		return;
	}

	// Compute pi
	for (m = size * np; m <= n; m += size * np)
	{
		pw = generate_points(np);
		MPI_Reduce(&pw, &pc, 1, MPI_INT, MPI_SUM, 0, comm);
		// Rank 0 prints the estimate
		if (rank == 0)
		{
			p += pc;
			pi = (double) 4 * p / m;
			if (m % (n / 10) == 0) printf("%ld %.20f\n", m, pi);
		}
	}
}

int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	pi_monte_carlo(atol(argv[1]), MPI_COMM_WORLD);
	MPI_Finalize();
	return 0;
}
