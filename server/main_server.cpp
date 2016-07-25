#include "udp_server.h"
using namespace std;

void* recv(void* arg)
{
	udp_server* _ser=(udp_server*)arg;
	while(1)
	{
		_ser->recv_data();
	}
}
void* broadcast(void* arg)
{
	udp_server* _ser=(udp_server*)arg;
	while(1)
	{
		_ser->broadcast_data();
	}
}

static void usage(const char* proc)
{
	cout<<"Usage: "<<proc<<" [ip|any] [port]"<<std::endl;
}
int main(int argc,char*argv[])
{
	if(argc!=3)
	{
		usage(argv[0]);
		exit(1);
	}
	string _ip=argv[1];
	short _port=atoi(argv[2]);

	//daemon(0,0);
	//
	udp_server _ser(_ip,_port);
	_ser.init();
	string _msg;
	pthread_t tr,tb;
	pthread_create(&tr,NULL,recv,(void*)&_ser);
	pthread_create(&tb,NULL,broadcast,(void*)&_ser);

	pthread_join(tr,NULL);
	pthread_join(tb,NULL);
	return 0;
}
