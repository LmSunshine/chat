#include "my_json.h"

my_json::my_json()
{}
my_json::~my_json()
{}
int my_json::serialize(Json::Value& _in_val,std::string& _out_str)
{
#ifdef DEBUG
	Json::StyledWriter _write;
	_out_str=_write.write(_in_val);
#else
	Json::FastWriter _write;
	_out_str=_write.write(_in_val);
#endif
	return 0;
}
int my_json::deserialize(Json::Value& _out_val,std::string& _in_str)
{
	Json::Reader _read;
	if(_read.parse(_in_str,_out_val,false))
		return 0;
	return 1;
}
