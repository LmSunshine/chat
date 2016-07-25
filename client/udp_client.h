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
#include<vector>
#include "comm.h"
#include "udp_data.h"
#include "chat_window.h"

using namespace std;

#define default_ip "127.0.0.1"
#define default_port 8080
#define _SIZE_ 10240

class udp_client
{
public:
	udp_client(const string& _ip=default_ip,const short& _port=default_port);
	void init();
//	int recv_data(string& _out);
	int recv_data();
	int send_data(string& _in);
	~udp_client();
	void add_friend(const string& _win_f);
	void del_friend(const string& _win_f);
	vector<string> clif;
private:
	string ip;
	short port;
	int sock;
};
