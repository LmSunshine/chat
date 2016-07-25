#include "data_pool.h"

data_pool::data_pool(int _cap)
	:pool(_cap)
	,capacity(_cap)
	,put_index(0)
	,get_index(0)
{
	sem_init(&sem_buf,0,_cap);
	sem_init(&sem_data,0,0);

}
//data_pool::data_pool(int _cap=256)
//	:pool(_cap)
//	,capacity(_cap)
//	,put_index(0)
//	,get_index(0)
//{
//	sem_init(&sem_buf,0,_cap);
//	sem_init(&sem_data,0,0);
//
//}
data_pool::~data_pool()
{
	sem_destroy(&sem_buf);
	sem_destroy(&sem_data);
}
void data_pool::data_put(std::string& _in)
{
	sem_wait(&sem_buf);
	//lock
	pool[put_index]=_in;
	put_index++;
	put_index%=capacity;
	//open lock
	sem_post(&sem_data);
}
void data_pool::data_get(std::string& _out)
{
	sem_wait(&sem_data);
	_out=pool[get_index];
	get_index++;
	sem_post(&sem_buf);
	get_index%=capacity;
}
