#include "udp_client.h"

using namespace std;

udp_client::udp_client(const string& _ip,const short& _port)
	:ip(_ip)
	,port(_port)
	,sock(-1)
{}
void udp_client::init()
{
	//
	sock=socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0)
	{
		print_log(__FUNCTION__,__LINE__,strerror(errno));
		exit(1);
	}
	//
//	struct sockaddr_in remote;
//	remote.sin_family=AF_INET;
//	remote.sin_port=htons(port);
//	remote.sin_addr.s_addr=inet_addr(ip.c_str());

}
//int udp_client::recv_data(string& _out)
int udp_client::recv_data()
{
	char buf[_SIZE_];
	buf[0]='\0';
	struct sockaddr_in server;
	socklen_t len=sizeof(server);
	ssize_t _s=recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&server,&len);
	if(_s<0)
	{
		print_log(__FUNCTION__,__LINE__,strerror(errno));
		exit(1);
	}
	else if(_s==0)
	{
		string msg="client shutdown...";
		print_log(__FUNCTION__,__LINE__,msg.c_str());
	}
	else
	{
		buf[_s]='\0';
	}
//	cout<<"server: [ "<<inet_ntoa(server.sin_addr) <<" ] [ "<<ntohs(server.sin_port)<<" ]# [ "<<buf<<" ]"<<endl;
	return _s;
}
int udp_client::send_data(string& _in)
{
	struct sockaddr_in remote;
	remote.sin_family=AF_INET;
	remote.sin_port=htons(port);
	remote.sin_addr.s_addr=inet_addr(ip.c_str());
	ssize_t _s=sendto(sock,_in.c_str(),_in.size(),0,(struct sockaddr*)&remote,sizeof(remote));
	if(_s<0)
	{
		print_log(__FUNCTION__,__LINE__,strerror(errno));
		exit(1);
	}
	return _s;
}
void udp_client::add_friend(const string& _win_f)
{
	vector<string>::iterator _iter=clif.begin();
	for(;_iter!=clif.end();_iter++)
	{
		if(*_iter==_win_f)
		{
			return;
		}
	}
	clif.push_back(_win_f);
}
void udp_client::del_friend(const string& _win_f)
{
	vector<string>::iterator _iter=clif.begin();
	for(;_iter!=clif.end();_iter++)
	{
		if(*_iter==_win_f)
		{
			_iter=clif.erase(_iter);
			return;
		}
	}
}
udp_client::~udp_client()
{
	close(sock);
}
