#include <iostream>
#include <fstream>
#include <fcntl.h>

#include "info.pb.h"
using namespace std;
/*
 * Author: chenping <chenping@autohome.com.cn>
 *
 * File: protobuf_serialize.cpp
 * Create Date: 2015-01-19 11:11:14
 *
 */

///
/// protobuf 的各种序列化和返序列化形式
///


record::info wp, rap;

//C数组的序列化和序列化API
//bool ParseFromArray(const void* data, int size);
//bool SerializeToArray(void* data, int size) const;
char parray[128] = "";
void set_people_1()             
{
	wp.set_name("sealyao");   
	wp.set_id(123456);        
	wp.set_email("chenping@163.com");
	wp.SerializeToArray(parray,256);
}

void get_people_1()             
{
	rap.ParseFromArray(parray,256);
	cout << "Get People from Array:" << endl;
	cout << "\t Name : " <<rap.name() << endl;
	cout << "\t Id : " << rap.id() << endl;
	cout << "\t email : " << rap.email() << endl;
}

//C++string序列化和序列化API
//bool SerializeToString(string* output) const;
//bool ParseFromString(const string& data);
std::string pstring;
void set_people_2()             
{
	wp.set_name("sealyao");   
	wp.set_id(123456);        
	wp.set_email("chenping@163.com");
	wp.SerializeToString(&pstring);
}

void get_people_2()             
{
	rap.ParseFromString(pstring);  
	cout << "Get People from String:" << endl;
	cout << "\t Name : " <<rap.name() << endl;
	cout << "\t Id : " << rap.id() << endl;
	cout << "\t email : " << rap.email() << endl;
}


//文件描述符的序列化和序列化API
//bool SerializeToFileDescriptor(int file_descriptor) const;
//bool ParseFromFileDescriptor(int file_descriptor);
int fd = 0;
void set_people_3(const char *path)
{
	fd = open(path,O_CREAT|O_TRUNC|O_RDWR,0644);
	if(fd <= 0){
		perror("open");
		exit(0); 
	}   
	wp.set_name("sealyaog");
	wp.set_id(123456);
	wp.set_email("chenping@163.com");
	wp.SerializeToFileDescriptor(fd);   
	close(fd);
}

void get_people_3(const char *path)
{
	fd = open(path,O_RDONLY);
	if(fd <= 0){
		perror("open");
		exit(0);
	}
	rap.ParseFromFileDescriptor(fd);
	std::cout << "Get People from FD:" << endl;
	std::cout << "\t Name : " <<rap.name() << endl;
	std::cout << "\t Id : " << rap.id() << endl;
	std::cout << "\t email : " << rap.email() << endl;
	close(fd);
}


//C++ stream 序列化/反序列化API
//bool SerializeToOstream(ostream* output) const;
//bool ParseFromIstream(istream* input);
void set_people_4(const char *path)
{
	fstream fs(path,ios::out|ios::trunc|ios::binary);
	wp.set_name("sealyaog");
	wp.set_id(123456);
	wp.set_email("chenping@163.com");
	wp.SerializeToOstream(&fs);    
	fs.close();
	fs.clear();
}

void get_people_4(const char *path)
{
	fstream fs(path,ios::in|ios::binary);
	rap.ParseFromIstream(&fs);
	std::cout << "\t Name : " <<rap.name() << endl;
	std::cout << "\t Id : " << rap.id() << endl; 
	std::cout << "\t email : " << rap.email() << endl;   
	fs.close();
	fs.clear();
}

int main(int argc, char* argv[])
{
	cout<<"(1) test c style.."<<endl;
	set_people_1();
	get_people_1();

	cout<<"(2) C++ string style.."<<endl;
	set_people_2();
	get_people_2();

	const char *path = "./test.txt";
	cout<<"(3) file descriptor style.."<<endl;
	set_people_3(path);
	get_people_3(path);

	cout<<"(4) C++ stream style.."<<endl;
	set_people_4(path);
	get_people_4(path);
	cout<<"all"<<endl;
	return 0;
}

