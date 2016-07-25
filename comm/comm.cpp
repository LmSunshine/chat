#include "comm.h"
//using namespace std;

void print_log(const std::string& function,int line,const char* msg)
{
	std::cout<<"[ "<<function<<" ] "<<"[ "<<line<<" ] "<<"[ "<<msg<<" ] "<<std::endl; 
}
