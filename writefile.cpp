#include "writefile.h"


writefile::writefile(){
}

writefile::writefile(std::vector<torrContent>& torr){
	this->torr = torr;
}

writefile::~writefile(){
}

void writefile::run(){
	std::ofstream ofs ("Torrent.csv", std::ofstream::out);
	int outSize = torr.size();

	if(ofs){
		for(int i = 0;i < outSize;i++){
			ofs << torr[i].filePath << "," << torr[i].fileName << std::endl;
		}
	}else{
		std::cout << "ERROR:Cant open output file!" <<std::endl;
	}

	ofs.close();
}
