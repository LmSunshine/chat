#include<iostream>
#include<vector>
#include <semaphore.h>
#include<string>

class data_pool
{
public:
	data_pool(int cap=256);
	~data_pool();
	void data_put(std::string& _in);
	void data_get(std::string& _out);
private:
	std::vector<std::string> pool;
	int capacity;
	int put_index;
	int get_index;
	sem_t sem_buf;
	sem_t sem_data;
};
