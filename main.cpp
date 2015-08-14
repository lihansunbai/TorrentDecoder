#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "decode.h"
#include "readfile.h"
#include "writefile.h"

int main(int argc,char** argv){
	std::string filedirction;
	
	readfile torrRe;
	std::cout << "START:extract torrent file information!"<<std::endl;

	std::vector<torrContent> files;  
	torrRe.getDirction(&filedirction);
	torrRe.getAllFiles(filedirction, files);
	torrRe.run();
	
	std::cout << "Dirction:"<<filedirction <<std::endl;
	std::cout << "SUCCESS:output all information in Torrent.csv!" <<std::endl;
	return 0;
}