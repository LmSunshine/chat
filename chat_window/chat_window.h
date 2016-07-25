#include<iostream>
#include<string>
#include<string.h>
#include<pthread.h>
#include<ncurses.h>

#define SIZE 1024

class chat_window
{
public:
	chat_window();
	~chat_window();
	void create_header();
	void create_output();
	void create_friendList();
	void create_input();
	WINDOW* create_newwin(int height,int width,int starty,int startx);
    WINDOW* getHeader();
    WINDOW* getOutput();
    WINDOW* getFriendList();
    WINDOW* getInput();
	void fflush_win(WINDOW* p);
	void clear_win_line(WINDOW* p,int begin,int lines);
	void put_str_to_win(WINDOW* win,int starty,int startx,const std::string& msg);
	std::string get_str_from_win(WINDOW* win);
	void* drawHeader(void* arg);
	void* drawOutput(void* arg);
	void* drawFriendList(void* arg);
	void* drawInput(void* arg);
//public:
private:
	WINDOW* header;
	WINDOW* output;
	WINDOW* friendList;
	WINDOW* input;
};
