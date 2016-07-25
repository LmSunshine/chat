#include "udp_client.h"
using namespace std;

udp_client* cli_p=NULL;
string nick_name;
string school;

static void usage(const char* proc)
{
	cout<<"Usage: "<<proc<<" [ip|any] [port]"<<std::endl;
}

static void* drawHeader(void* arg)
{
	chat_window* winp=(chat_window*)arg;
	std::string _msg="Welcome!";
	winp->create_header();

	int _max_y,_max_x;
	getmaxyx(winp->getHeader(),_max_y,_max_x);
	int _y=_max_y/2;
	int _x=0;

	while(1)
	{
		winp->put_str_to_win(winp->getHeader(),_y,_x,_msg);
		winp->fflush_win(winp->getHeader());
		usleep(100000);
		winp->clear_win_line(winp->getHeader(),_y,2);
		_x++;
		_x%=_max_x;
	}
}
static void* drawOutput(void* arg)
{
	std::string msg;
	chat_window* winp=(chat_window*)arg;
	winp->create_output();
	int _max_y,_max_x;
	getmaxyx(winp->getOutput(),_max_y,_max_x);

	winp->create_friendList();
	int _max_fy,_max_fx;
	getmaxyx(winp->getFriendList(),_max_fy,_max_fx);

	udp_data data;
	std::string _nick_name;
	std::string _msg;
	std::string _school;
	std::string _cmd;
	std::string _win_out;
	std::string _win_f;

	while(1)
	{
		cli_p->recv_data();
		data.to_value(_nick_name,_msg,_school,_cmd,msg);
		_win_out=_nick_name;
		_win_out+="-";
		_win_out+=_school;
		_win_f=_win_out;
		_win_out+="#";
		_win_out+=_msg;

		cli_p->add_friend(_win_f);
		if(_cmd=="quit")
		{
			cli_p->del_friend(_win_f);
		}
		int _y=1;
		if(_y>=_max_y)
		{
			_y=1;
			winp->clear_win_line(winp->getOutput(),1,_max_y-1);
		}
		winp->put_str_to_win(winp->getOutput(),_y++,3,_win_out);//3->1
		winp->fflush_win(winp->getOutput());
		usleep(1000000);

		int size=(cli_p->clif).size();
		int page=size/(_max_fy-3);//why-3
		int mode=size%(_max_fy-3);
		if(mode!=0)
		{
			page++;
		}
		int i=0;
		while(i<size)
		{
			winp->put_str_to_win(winp->getFriendList(),++i,3,cli_p->clif[i]);
		}
		winp->fflush_win(winp->getFriendList());
	}
}
//void* drawFriendList(void* arg)
//{
//	chat_window* winp=(chat_window*)arg;
//	winp->create_friendList();
//	while(1)
//	{
//		winp->fflush_win(winp->getFriendList());
//		usleep(1000000);
//	}
//}
static void* drawInput(void* arg)
{
	chat_window* winp=(chat_window*)arg;
	winp->create_input();
	std::string _msg="Please input# ";
	
	int _max_y,_max_x;
	getmaxyx(winp->getInput(),_max_y,_max_x);

	std::string _cmd="None";
	udp_data _data;
	std::string _out;

	while(1)
	{
		winp->put_str_to_win(winp->getInput(),1,1,_msg);
		winp->fflush_win(winp->getInput());
		std::string _in=winp->get_str_from_win(winp->getInput());
		usleep(1000000);
		winp->clear_win_line(winp->getInput(),1,_max_y-2);

		if(_in=="q"||_in=="quit"||_in=="Q"||_in=="QUIT")
		{
			_cmd="quit";
			_data.to_string(nick_name,_in,school,_cmd,_out);
			cli_p->send_data(_out);
			exit(0);
		}
		_data.to_string(nick_name,_in,school,_cmd,_out);
		cli_p->send_data(_out);
		usleep(1000);
	}
}


int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		usage(argv[0]);
		exit(1);
	}
	std::string _ip=argv[1];
	short _port=atoi(argv[2]);

	std::cout<<"please input your nick_name: ";
	fflush(stdout);
	std::cin>>nick_name;
	std::cout<<"please input your school: ";
	fflush(stdout);
	std::cin>>school;

	udp_client _cli(_ip,_port);
	_cli.init();
	cli_p=&_cli;

	chat_window _win;
	pthread_t th,to,tf,ti;

	pthread_create(&th,NULL,drawHeader,(void*)&_win);
	pthread_create(&to,NULL,drawOutput,(void*)&_win);
//	pthread_create(&tf,NULL,drawFriendList,(void*)&_win);
	pthread_create(&ti,NULL,drawInput,(void*)&_win);
	
	pthread_join(th,NULL);
	pthread_join(to,NULL);
//	pthread_join(tf,NULL);
	pthread_join(ti,NULL);

	return 0;
}
//int main()
//{
//	string msg="hello";
//	udp_client cli;
//	cli.init();
//	cli.send_data(msg);
//	cli.recv_data();
//	return 0;
//}

//int main()
//{
//	chat_window _win;
//	pthread_t th,to,tf,ti;
//
//	pthread_create(&th,NULL,drawHeader,(void*)&_win);
//	pthread_create(&to,NULL,drawOutput,(void*)&_win);
//	pthread_create(&tf,NULL,drawFriendList,(void*)&_win);
//	pthread_create(&ti,NULL,drawInput,(void*)&_win);
//	
//	pthread_join(th,NULL);
//	pthread_join(to,NULL);
//	pthread_join(tf,NULL);
//	pthread_join(ti,NULL);
//
//	return 0;
//}
