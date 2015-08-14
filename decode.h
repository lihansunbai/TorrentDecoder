#pragma once
#include <iostream>
#include <string>
#include <string>
#include <fstream>
#include <vector>

typedef struct torrContent{
	std::string filePath;
	std::string fileName;
};

class decode
{
public:
	decode();
	decode(std::string str,std::string *name,torrContent* torr);
	~decode();
	int run(const std::string* str);
	std::string *name;
	
protected:
	std::string scrstr;
	torrContent* torr;

	int deStr(const std::string* str);
	int deDic(const std::string* str);
	int deInt(const std::string* str);
	int deList(const std::string* str);

	bool IsVedio(const std::string* str);
};

