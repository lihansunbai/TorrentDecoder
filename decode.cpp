#include "decode.h"


decode::decode(){
}

//construct function, set up the string to decode
decode::decode(std::string str,std::string *name,torrContent* torr){
	this->scrstr = str;
	this->name = name;
	this->torr = torr;
}

decode::~decode(){
}

//detect decode function
int decode::run(const std::string* str){
	int count = (*str).length();
	int i = 0;
	std::string temp = (*str);

	//compare string character with ascii
	//number<=57,d = 100,i = 105,l = 108,e = 100
	while ( i < count){
		temp =  str->substr(i);
		if((*str)[i] < 58){
			i += this->deStr(&temp);
		}else if((*str)[i] == 100){
			i += this->deDic(&temp);
		}else if((*str)[i] == 105){
			i += this->deInt(&temp);
		}else if((*str)[i] == 108){
			i += this->deList(&temp);
		}else if((*str)[i] == 101){
			i++;
			break;
		}else{
			std::cout << "ERROR:File is not torrent file or file is broken!" << std::endl;
			break;
		}
	}
	return i;
}

//decode type string
//temp2 is the content of bencode
int decode::deStr(const std::string* str){
	int i = 0;

	//string length
	int len = 0;

	//position of ':'
	int pos = 0;

	//return value
	int re = 0;
	std::string temp = *str;

	//get length of string-type 
	std::string temp1 = *str;

	//get content of string-type 
	std::string temp2 = *str;

	while(i < temp.length()){
		if(temp[i] == ':'){
			pos = temp.find(':');
			temp1 = temp.substr(0,pos);
			len  = std::stoi(temp1);

			//maybe its no matter with '\n'
			temp2 = temp.substr(pos + 1,len);
			re = pos + 1 + len;
			i += temp.length();
		}else{
			i++;
		}
	}

	//check wheather a vedio file
	//get a max enough number to end the iterate 
	if(IsVedio(&temp2)){
		pos = temp2.find_last_of('.');
		temp2 = temp2.substr(0,pos); 
		*this->name = temp2;
		std::cout << temp2 << std::endl;
		torr->fileName = temp2;
		return temp.length();
	}

	return re;
}

//decode type of dictionary
int decode::deDic(const std::string* str){
	int pos = 0;
	std::string temp = (*str);
	temp =  str->substr(1);

	//use function run,which iterative decode type of dictionary
	pos = run(&temp);
	return pos + 1;
}

//decode type of integer
int decode::deInt(const std::string* str){
	long number  = 0;
	int pos = 0;
	int len = 0;
	std::string temp;

	pos = str->find('e');

	//cant use "stoi" function
	//because of it is to long that may out of memery.
	//so use "strtol" funciton
	temp = str->substr(1,(pos-1));
	const char* num = temp.c_str();
	number = strtol(num,NULL,10);

	return pos + 1;
}

//decode type of list
int  decode::deList(const std::string* str){
	int pos = 0;
	std::string temp = (*str);
	temp =  str->substr(1);
	pos = run(&temp);
	return pos + 1;
}

bool decode::IsVedio(const std::string* str){
	std::string vedio[10] = {".avi" ,".rmvb" ,".rm" ,".mpg" ,".mpeg" ,".wmv" ,".mp4" ,".mkv" ,".ISO" ,".wma"};

	for(int i = 0;i < 10;i++){
		if(str->find(vedio[i]) != (-1)){
			return true;
		}
	}
	return false;
}
