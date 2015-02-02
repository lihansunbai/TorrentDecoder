#include "readfile.h"

readfile::readfile(){
}

readfile::readfile(std::string filedirction,std::vector<std::string>& files){
	this->filedirction = filedirction;
	this->files = files;
}

readfile::~readfile()
{
}

void readfile::getAllFiles( std::string path, std::vector<std::string>& files){
	long   hFile   =   0;  
	struct _finddata_t fileinfo;  
	std::string p;
	if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1){  
		do {
			if((fileinfo.attrib &  _A_SUBDIR)){  
				if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0){
					files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
				}
			}else{  
				files.push_back(p.assign(path).append("\\").append(fileinfo.name) );  
			}  
		}while(_findnext(hFile, &fileinfo)  == 0); 
		_findclose(hFile); 
	}

	this->files = files;
}

void readfile::getDirction(std::string* filedirction){
	char *buffer;
	//也可以将buffer作为输出参数
	if((buffer = getcwd(NULL, 0)) == NULL){
		std::cout << "cant get dirction" << std::endl;
	}else{
		//this->filedirction.assign(buffer);
		this->filedirction = "E:\\wallpaper\\workplace\\torrent";
		*filedirction = this->filedirction;
		free(buffer);
	}
}

void readfile::run(){
	std::fstream torrent;
	 
	for(int i = 0;i <this->files.size();i++){
		torrent.open(files[i]);
		std::string temp;
		std::string temp1 = "unkonw";
		if(torrent.is_open()){
			int len = 999999;
			char *buf = new char[len];
			torrent.read(buf,len);
			temp.assign(buf);
			decode de(temp,&temp1);
			de.run(&temp);
			std::cout << temp1 << std::endl;
			delete buf;
		}
		
		torrent.close();
	}
}