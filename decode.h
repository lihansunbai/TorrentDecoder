#pragma once
#include <iostream>
#include <string>

class decode
{
public:
	decode();
	decode(std::string str,std::string *name);
	~decode();
	int run(const std::string* str);
	std::string *name;
protected:
	std::string scrstr;
	

	int deStr(const std::string* str);
	int deDic(const std::string* str);
	int deInt(const std::string* str);
	int deList(const std::string* str);

	bool IsVedio(const std::string* str);
};

