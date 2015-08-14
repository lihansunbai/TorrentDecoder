#include "readfile.h"

readfile::readfile(){
}

readfile::readfile(std::string filedirction,std::vector<torrContent>& torr){
	this->filedirction = filedirction;
	this->torrent = torr;
}

readfile::~readfile()
{
}

void readfile::getAllFiles( std::string path, std::vector<torrContent>& torr){
	long   hFile   =   0;  
	struct _finddata_t fileinfo;  
	std::string p;
	if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1){  
		do {
			if((fileinfo.attrib &  _A_SUBDIR)){  
				if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0){
					torrContent to;
					to.filePath = p.assign(path).append("\\").append(fileinfo.name);
					to.fileName = "unknow";

					torr.push_back(to);
				}
			}else{
				torrContent to;
				to.filePath = p.assign(path).append("\\").append(fileinfo.name) ;
				to.fileName = "unknow";

				torr.push_back(to);  
			}  
		}while(_findnext(hFile, &fileinfo)  == 0); 
		_findclose(hFile); 
	}

	this->torrent = torr;
}

void readfile::getDirction(std::string* filedirction){
	char *buffer;
	//也可以将buffer作为输出参数
	if((buffer = getcwd(NULL, 0)) == NULL){
		std::cout << "cant get dirction" << std::endl;
	}else{
		//save file path
		this->filedirction.assign(buffer);

		//test file path
		//this->filedirction = "E:\\wallpaper\\workplace";
		//this->filedirction = "D:\\Voluptuous\\fans";


		*filedirction = this->filedirction;
		free(buffer);
	}
}


//all proccess done in this function
void readfile::run(){
	std::ifstream torrents;
	

	int filesSize = this->torrent.size();

	for(int i = 0;i < filesSize;i++){
		std::string temp = "unknow";
		torrents.open(this->torrent[i].filePath,std::ifstream::binary);

		//previous files read methoes.
		//ABANDONED!!!
		/*std::string temp;
		std::string temp1 = "unknow";
		if(torrent.is_open()){
		int len = 999999;
		char *buf = new char[len];
		torrent.read(buf,len);
		temp.assign(buf);
		decode de(temp,&temp1);
		de.run(&temp);
		std::cout << temp1 << std::endl;
		delete buf;
		}*/
		//ABANDONED!!!

		if(torrents){
			//get the file length
			torrents.seekg(0,torrents.end);
			int length = torrents.tellg();
			torrents.seekg(0,torrents.beg);

			// allocate file content memory:
			char * buffer = new char[length];

			//read content to buffer
			torrents.read(buffer,length);

			//torrent file begin with a Dictonary.
			//it mean if file did not start with a 'd'.
			//it may not a torrent file or the file is broken.
			if(buffer[0] == 100){
				std::string content(buffer,length);

				std::cout << this->torrent[i].filePath << std::endl;
				decode de(content,&temp,&this->torrent[i]);
				de.run(&content);
				this->torrent[i].fileName = *de.name;
			}
		}else{
			std::cout << "ERROR: Cant open file \"" << this->torrent[i].filePath << "\"." << std::endl; 
		}

		torrents.close();
	}
	writefile write(this->torrent);
	write.run();
}

