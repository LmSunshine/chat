#include<iostream>
#include<string>
#include "json/json.h"
#include "my_json.h"
class udp_data
{
public:
//	udp_data(std::string _nick_name,std::string _msg,std::string _school,std::string _cmd);
    udp_data();
	~udp_data();
	void to_string(std::string _in_nick_name,std::string _in_msg,std::string _in_school,std::string _in_cmd,std::string &_out_string);
void to_value(std::string& _out_nick_name,std::string& _out_msg,std::string& _out_school,std::string& _out_cmd,std::string& _in_string);
//void to_value(std::string& _in_string);
private:
	std::string nick_name;
	std::string msg;
	std::string school;
	std::string cmd;
};
