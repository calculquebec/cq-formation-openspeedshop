#include <cstdlib>
#include <string>
#include "io_utils.h"
using namespace std;
int main(int argc, char * argv[])
{
	size_t size = 1000000;
	string filename = "mydata.dat";
	if (argc > 1) 
		size = atol(argv[1])*1000000;
	else {
		cerr << "Error, must specify the size." << endl;
		exit(1);
	}
	if (argc > 2)
	{
		filename = string(argv[2]);
	}
	cout << "Performing operations with " << size/1000000. << "M points." << endl;
	write_data(size, filename);
	read_data(size, filename);	
}

