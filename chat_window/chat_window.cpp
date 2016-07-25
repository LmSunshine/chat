#include "chat_window.h"

chat_window::chat_window()
{
	initscr();
}
chat_window::~chat_window()
{
//	destory_win(getHeader());
//	destory_win(getOutput());
//	destory_win(getFriendList());
//	destory_win(getInput);

    delwin(getHeader());
	delwin(getOutput());
	delwin(getFriendList());
	delwin(getInput());
	endwin();
}
void chat_window::create_header()
{
	int _h=LINES/5;
	int _w=COLS;
	int _y=0;
	int _x=0;

	header=create_newwin(_h,_w,_y,_x);
	fflush_win(header);
}
void chat_window::create_output()
{
	int _h=(LINES*3)/5;
	int _w=(COLS*3)/4;
	int _y=LINES/5;
	int _x=0;
	output=create_newwin(_h,_w,_y,_x);
	fflush_win(getOutput());
}
void chat_window::create_friendList()
{
	int _h=(LINES*3)/5;
	int _w=COLS/4;
	int _y=LINES/5;
	int _x=(COLS*3)/4;
	friendList=create_newwin(_h,_w,_y,_x);
	fflush_win(getFriendList());
}
void chat_window::create_input()
{
	int _h=LINES/5;
	int _w=COLS;
	int _y=(LINES*4)/5;
	int _x=0;
	input=create_newwin(_h,_w,_y,_x);
	fflush_win(getInput());
}
WINDOW* chat_window:: create_newwin(int height,int width,int starty,int startx)
{
	WINDOW* local_win=newwin(height,width,starty,startx);
	box(local_win,0,0);
	return local_win;
}
WINDOW* chat_window::getHeader()
{
	return header;
}
WINDOW* chat_window::getOutput()
{
	return output;
}
WINDOW* chat_window::getFriendList()
{
	return friendList;
}
WINDOW* chat_window::getInput()
{
	return input;
}
void chat_window::put_str_to_win(WINDOW* win,int starty,int startx,const std::string& msg)
{
	mvwaddstr(win,starty,startx,msg.c_str());
}
std::string chat_window::get_str_from_win(WINDOW* win)
{
	char msg[SIZE];
	memset(msg,'\0',sizeof(msg));
	wgetnstr(win,msg,SIZE);
	return msg;
}
void chat_window::fflush_win(WINDOW* p)
{
	box(p,0,0);
	wrefresh(p);
}
void chat_window::clear_win_line(WINDOW* p,int begin,int lines)
{
	while(lines--)
	{
		wmove(p,begin++,0);
		wclrtoeol(p);
	}
}
void* drawHeader(void* arg)
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
void* drawOutput(void* arg)
{
	chat_window* winp=(chat_window*)arg;
	winp->create_output();
	while(1)
	{
		winp->fflush_win(winp->getOutput());
		usleep(1000000);
	}
}
void* drawFriendList(void* arg)
{
	chat_window* winp=(chat_window*)arg;
	winp->create_friendList();
	while(1)
	{
		winp->fflush_win(winp->getFriendList());
		usleep(1000000);
	}
}
void* drawInput(void* arg)
{
	chat_window* winp=(chat_window*)arg;
	winp->create_input();
	std::string _msg="Please input# ";
	
	int _max_y,_max_x;
	getmaxyx(winp->getInput(),_max_y,_max_x);

	while(1)
	{
		winp->put_str_to_win(winp->getInput(),1,1,_msg);
		winp->fflush_win(winp->getInput());
		winp->get_str_from_win(winp->getInput());
		usleep(1000000);
		winp->clear_win_line(winp->getInput(),1,_max_y-2);
	}
}


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
