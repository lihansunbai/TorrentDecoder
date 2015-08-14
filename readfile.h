#pragma once
#include <io.h>
#include <stdio.h>
#include <iostream>
#include <direct.h>
#include <string>
#include <fstream>
#include <vector>
#include "decode.h"
#include "writefile.h"


class readfile
{
public:
	readfile();
	readfile(std::string filedirction,std::vector<torrContent>& torr);
	void getDirction(std::string* filedirction);
	void getAllFiles( std::string path, std::vector<torrContent>& torr);
	void run();
	
	~readfile();
protected:
	
	std::string filedirction;
	//std::vector<std::string> files;
	std::vector<std::string> fileNames;

	std::vector<torrContent> torrent;
};

