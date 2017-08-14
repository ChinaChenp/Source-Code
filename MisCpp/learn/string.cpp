#include <string.h>

#include <iostream>
#include <vector>
using namespace std;

/*
 * String
 */

class String
{
public:
	String():size_(0),data_(new char[1]) {
        data_[0] = '\0';
    }

	String(const char *str):size_(strlen(str)),data_(new char[size_ + 1]) {
        strcpy(data_, str);
    }

	~String(){delete [] data_;}

	String(const String &rs):size_(rs.size_),data_(new char[rs.size_]) {
        strcpy(data_, rs.data_);
    }

	String & operator=(const String &rs) {
		String tmp(rs);
		std::swap(data_, tmp.data_);
		size_ = rs.size_;
		return *this;
	}

	//char operator
	const char &operator[](size_t index) {
		if(index >= 0 && index < size_)
			return data_[index];
	}

	String operator+(const String &other) {
		String tmp;
		if(!data_) {
			tmp = other;
        }

		if(!other.data_) {
			tmp = *this;
        } else {
			tmp.size_ = size_ + other.size_;
			tmp.data_ = new char[tmp.size_ + 1];
			strcpy(tmp.data_, data_);
			strcat(tmp.data_, other.data_);
		}
		return tmp;
	}
	const char *c_str()
	{return data_;}

	size_t size()
	{return size_;}
	size_t length()
	{return size_;}

	bool empty()
	{return size_ == 0;}

	friend ostream & operator<<(ostream &os, const String &s) {
		os << s.data_;
		return os;
	}

	friend bool operator==(const String &s1, const String &s2) {
		return (s1.size_ == s2.size_ && strcmp(s1.data_, s2.data_) == 0);
	}

	friend bool operator>(const String &s1, const String &s2) {
		return (strcmp(s1.data_, s2.data_) > 0);
	}

	friend bool operator<(const String &s1, const String &s2) {
		return (strcmp(s1.data_, s2.data_) < 0);
	}

private:
	size_t size_;
	char *data_;
};

/// ------------------------test-----------------------------
void foo(String x) {
	cout<<"x = "<<x<<" (test by value)"<<endl;
}

void bar(const String& x) {
	cout<<"tmp = "<<x<<" (test by ref)"<<endl;
}

String baz() {
	String ret("world");
	return ret;
}

int main(int argc, char* argv[]) {
	String s0;
	String s1("hello");
	String s2(s0);
	String s3 = "is s3";

	cout<<"s0 = "<<s0<<", size="<<s0.size()<<endl;
	cout<<"s1 = "<<s1<<", size="<<s1.size()<<endl;
	cout<<"s2 = "<<s2<<endl;
	cout<<"s3 = "<<s3<<endl;
	String s4 = s1;
	s2 = s1;

	cout<<"s4 = "<<s4<<endl;
	cout<<"new s2 = "<<s2<<endl;

	String s6 = s2 + s3;
	cout<<"s2 + s3 = "<<s6<<endl;
	cout<<"s1<s2? "<<(s1<s2)<<endl;

	//pass string
	foo(s1);
	bar(s1);
	foo("temporary");
	bar("temporary");
	String s5 = baz();
	cout<<"s5 = "<<s5<<endl;

	//string in vector
	std::vector<String> svec;
	svec.push_back(s0);
	svec.push_back(s1);
	svec.push_back(baz());
	svec.push_back("good job");
	std::vector<String>::iterator it = svec.begin();
	for(; it != svec.end(); ++it)
		cout<<*it<<endl;
	return 0;
}

