#include "udp_server.h"

using namespace std;

udp_server::udp_server(const string _ip,const short _port)
	:ip(_ip)
	,port(_port)
	,sock(-1)
	,msg_pool(64)
{}
void udp_server::init()
{
	//
	sock=socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0)
	{
		print_log(__FUNCTION__,__LINE__,strerror(errno));
		exit(1);
	}
	//
	struct sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_port=htons(port);
	if(ip=="any")
		local.sin_addr.s_addr=htonl(INADDR_ANY);
	else
		local.sin_addr.s_addr=inet_addr(ip.c_str());
	socklen_t len=sizeof(local);
	if(bind(sock,(struct sockaddr*)&local,len)<0)
	{
		print_log(__FUNCTION__,__LINE__,strerror(errno));
		exit(2);
	}
}
int udp_server::recv_data()
{
	char buf[_SIZE_];
	buf[0]='\0';
	struct sockaddr_in client;
	socklen_t len=sizeof(client);
	ssize_t _s=recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&client,&len);
	if(_s<0)
	{
		print_log(__FUNCTION__,__LINE__,strerror(errno));
		exit(1);
	}
	else if(_s==0)
	{
		std::string msg="client shutdown...";
		print_log(__FUNCTION__,__LINE__,msg.c_str());
		exit(1);
	}
	else
	{
		buf[_s]='\0';
		string _out=buf;
		msg_pool.data_put(_out);
		print_log(__FUNCTION__,__LINE__,_out.c_str());
		
		std::string _key_ip=inet_ntoa(client.sin_addr);
		print_log(__FUNCTION__,__LINE__,_key_ip.c_str());
		add_user(_key_ip,client);
		del_user(_key_ip,_out);

//		cout<<"client: [ "<<inet_ntoa(client.sin_addr) <<" ] [ "<<ntohs(client.sin_port)<<" ]# [ "<<buf<<" ]"<<endl;
		return _s;
	}
}
int udp_server::send_data(struct sockaddr_in client,socklen_t len,string& msg)
{
	ssize_t _s=sendto(sock,msg.c_str(),msg.size(),0,(struct sockaddr*)&client,len);
	if(_s<0)
	{
		print_log(__FUNCTION__,__LINE__,strerror(errno));
		exit(1);
	}
	return _s;
}

int udp_server::broadcast_data()
{
	string _msg;
	msg_pool.data_get(_msg);
    std::map<std::string,struct sockaddr_in>::iterator _iter=online_user.begin();
	for(;_iter!=online_user.end();_iter++)
	{
		send_data(_iter->second,(socklen_t)sizeof(_iter->second),_msg);
	}
	return 0;
}
udp_server::~udp_server()
{
	close(sock);
}
void udp_server::add_user(string& _key_ip,struct sockaddr_in& client)
{
	std::map<std::string,struct sockaddr_in>::iterator _iter=online_user.find(_key_ip);
	if(_iter==online_user.end())
	{
		online_user.insert(std::pair<std::string,struct sockaddr_in>(_key_ip,client));
	}
	else
	{
		return;
	}
}
void udp_server::del_user(string& _key_ip,string& msg)
{
	string _name;
	string _school;
	string _msg;
	string _cmd;

	udp_data data;
	data.to_value(_name,_msg,_school,_cmd,msg);
	if(_cmd=="quit")
	{
		online_user.erase(_key_ip);
	}
}
