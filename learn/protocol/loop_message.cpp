#include <iostream>
#include <fstream>
#include <fcntl.h>

#include "loop_message.pb.h"
using namespace std;
/*
 * Author: chenping <chenping@autohome.com.cn>
 *
 * File: protobuf_serialize.cpp
 * Create Date: 2015-01-19 11:11:14
 *
 */

///
/// protobuf 嵌套message的定义和使用 
///


record::info::base wp; // or info_base
record::info all;

char parray[128] = "";
void set_people_1()             
{
	record::info::base *first = all.mutable_first();
	first->set_name("sealyao");
	first->set_id(12345);
	first->set_email("chenping@163.com");
	all.set_num(1);
	all.SerializeToArray(parray,256);
}

void get_people_1()             
{
	all.ParseFromArray(parray,256);
	wp = all.first();
	cout << "Get People from Array:" << endl;
	cout << "\t Name : " <<wp.name() << endl;
	cout << "\t Id : " << wp.id() << endl;
	cout << "\t email : " << wp.email() << endl;
	cout << "\t num : "<<all.num()<<endl;
}

int main(int argc, char* argv[])
{
	cout<<"(1) test c style.."<<endl;
	set_people_1();
	get_people_1();

	return 0;
}

