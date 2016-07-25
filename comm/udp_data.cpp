#include "udp_data.h"

//udp_data::udp_data(std::string _nick_name,std::string _msg,std::string _school,std::string _cmd)
//	:nick_name(_nick_name)
//	,msg(_msg)
//	,school(_school)
//	,cmd(_cmd)
//{}

udp_data::udp_data()
{}

udp_data::~udp_data()
{}
void udp_data::to_string(std::string _in_nick_name,std::string _in_msg,std::string _in_school,std::string _in_cmd,std::string& _out_string)
{
	nick_name=_in_nick_name;
	msg=_in_msg;
	school=_in_school;
	cmd=_in_cmd;

	Json::Value root;
	root["nick_name"]=nick_name;
	root["msg"]=msg;
	root["school"]=school;
	root["cmd"]=cmd;

	my_json::serialize(root,_out_string);
}
//void udp_data::to_string(std::string& _out_string)
//{
//	Json::Value root;
//	root["nick_name"]=nick_name;
//	root["msg"]=msg;
//	root["school"]=school;
//	root["cmd"]=cmd;
//	my_json::serialize(root,_out_string);
//}

//void udp_data::to_value(std::string& _out_nick_name,std::string& _out_msg,std::string& _out_school,std::string& _out_cmd,std::string& _in_string)
//{
//	Json::Value val;
//	my_json::deserialize(_in_string,val);
//
//	_out_nick_name=val["nick_name"].asString();
//	_out_msg=val["msg"].asString();
//	_out_school=val["school"].asString();
//	_out_cmd=val["cmd"].asString();
//
//	nick_name=_out_nick_name;
//	msg=_out_msg;
//	school=_out_school;
//	cmd=_out_cmd;
//}

void udp_data::to_value(std::string& _out_nick_name,std::string& _out_msg,std::string& _out_school,std::string& _out_cmd,std::string& _in_string)
{
	Json::Value val;
	my_json::deserialize(val,_in_string);

	
	_out_nick_name=val["nick_name"].asString();
	_out_msg=val["msg"].asString();
	_out_school=val["school"].asString();
	_out_cmd=val["cmd"].asString();

	nick_name=_out_nick_name;
	msg=_out_msg;
	school=_out_school;
	cmd=_out_cmd;

	std::cout<<"nick_name:"<<nick_name<<std::endl;
	std::cout<<"msg:"<<msg<<std::endl;
	std::cout<<"school:"<<school<<std::endl;
	std::cout<<"cmd:"<<cmd<<std::endl;
}

//void udp_data::to_value(std::string& _in_string)
//{
//	Json::Value val;
//	my_json::deserialize(_in_string,val);
//}
//int main()
//{
//	udp_data _data;
//	std::string out_string;
//	_data.to_string("luu","beautiful","XPU","dancing",out_string);
//	std::cout<<out_string;
//
////	std::string in_string="{luu beautiful XPU dancing}";
////	std::string in_string="{\"cmd\":\"dancing\",\"msg\":\"beautiful\",\"nick_name\":\"luu\",\"school\":\"XPU\"}";
////	_data.to_value(in_string);
//	return 0;
//}


//int main()
//{
//	udp_data _data;
//	std::string out_string;
//	_data.to_string("luu","beautiful","XPU","dancing",out_string);
//	std::cout<<out_string;
//
////	std::string in_string="{luu beautiful XPU dancing}";
////	std::string in_string="{\"cmd\":\"dancing\",\"msg\":\"beautiful\",\"nick_name\":\"luu\",\"school\":\"XPU\"}";
////	_data.to_value(in_string);
//	return 0;
//}


