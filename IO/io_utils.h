#ifndef io_utils_h
#define io_utils_h
#include <sys/stat.h>
#include <string>
#include <iostream>

void write_data(size_t size, const std::string & filename="mydata.txt");
void read_data(size_t size, const std::string & filename="mydata.txt");
inline void output_average_speed(const std::string & filename, double duration)
{
	struct stat filestatus;
	stat(filename.c_str(),&filestatus);
	long filesize = filestatus.st_size;
	std::cout << "File size: " << filesize/1024./1024 << "MB. Average speed : " << filesize/duration/1024/1024 << " MB/s" << std::endl;
}


#endif

