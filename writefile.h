#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "decode.h"



class writefile
{
public:
	writefile();
	writefile(std::vector<torrContent>& torr);
	~writefile();

	void run();

private:
	std::vector<torrContent> torr;
};

