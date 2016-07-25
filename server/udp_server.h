#include<iostream>
#include<string>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<pthread.h>
#include <map>
#include "udp_data.h"
#include "comm.h"
#include "data_pool.h"

#define default_ip "127.0.0.1"
#define default_port 8080
#define _SIZE_ 10240

//using namespace std;

class udp_server
{
public:
	udp_server(const std::string _ip=default_ip,const short _port=default_port);
	void init();
	int recv_data();
	int send_data(struct sockaddr_in client,socklen_t len,std::string& msg);
	int broadcast_data();
	~udp_server();
protected:
	void add_user(std::string& _key_ip,struct sockaddr_in& client);
	void del_user(std::string& _key_ip,std::string& msg);
private:
	std::string ip;
	short port;
	int sock;
	std::map<std::string,struct sockaddr_in> online_user;
	data_pool msg_pool;
};
