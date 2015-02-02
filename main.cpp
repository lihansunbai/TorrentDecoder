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

	writefile torrWr;

	//std::string str = "d8:announce44:udp://tracker.openbittorrent.com:80/announce13:announce-list9:n1007.mp4ll44:udp://tracker.openbittorrent.com:80/announce38:udp://tracker.publicbt.com:80/announce32:udp://tracker.ccc.de:80/announcei1415275147ee6:lengthi1048576000eee";
	//std::string name = "a";
	//decode torrDe(str,&name);
	//torrDe.run(&str);

	char * filePath = "D:\\Voluptuous\\fans";  
	std::vector<std::string> files;  
	torrRe.getDirction(&filedirction);
	torrRe.getAllFiles(filedirction, files);
	torrRe.run();
	
	std::cout << filedirction <<std::endl;
	std::cout << "Hello world!" <<std::endl;
	return 0;
}