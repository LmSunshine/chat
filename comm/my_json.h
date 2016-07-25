#include<iostream>
#include<unistd.h>
#include<string>
#include "json/json.h"

class my_json
{
public:
	my_json();
	~my_json();
	static int serialize(Json::Value& _val,std::string& _out_str);
	static int deserialize(Json::Value& _val,std::string& _in_str);
private:
	Json::Value val;
	std::string str;
};
