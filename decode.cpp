#include "decode.h"


decode::decode(){
}

//construct function, set up the string to decode
decode::decode(std::string str,std::string *name){
	this->scrstr = str;
	this->name = name;
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
		}

		//jurdg end of Dictionary or List
		//e is the flag of dictonary or list end
		if((*str)[i] == 101){
			return i+1;
		}	
	}
}

//decode type string
//temp2 is the content of bencode
int decode::deStr(const std::string* str){
	int i = 0;
	int len = 0;
	int pos = 0;
	int re = 0;
	std::string temp = *str;
	std::string temp1 = *str;
	std::string temp2 = *str;

	while(i < temp.length()){
		if(temp[i] == ':'){
			pos = temp.find(':');
			temp1 = temp.substr(0,pos);
			len  = std::stoi(temp1);
			//if consis of \n,do more change
			std::string tt = temp.substr(pos + 1,len);
			if(tt.find('\n' ) == -1){
				temp2 = temp.substr(pos + 1,len);
				re = pos  + len + 1;
			}else{
				temp2 = temp.substr(pos + 1,len-1);
				re =pos  + len;
			}
			i += pos + len;
			temp = temp.substr(0,i);
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
		return temp.length();
	}

	return re;
}

//decode type of dictionary
int decode::deDic(const std::string* str){
	int pos = 0;
	std::string temp = (*str);
	temp =  str->substr(1);
	//std::cout << "BEGIN OF DICTIONARY" << std::endl;

	//use function run,which iterative decode type of dictionary
	pos = run(&temp);

	//std::cout << "END OF DICTIONARY" << std::endl;

	return pos + 1;
}

//decode type of integer
int decode::deInt(const std::string* str){
	int number  = 0;
	int pos = 0;
	int len = 0;
	std::string temp = (*str);
	std::string temp1 = (*str);

	pos = str->find('e');

	temp1 = str->substr(0,(pos+1));
	len = temp1.length();

	temp = str->substr(1,(pos-1));
	number = std::stoi(temp);
	//std::cout << "number = " << number << std::endl;
	return len;
}

//decode type of list
int  decode::deList(const std::string* str){
	int pos = 0;
	std::string temp = (*str);
	temp =  str->substr(1);
	///std::cout << "BEGIN OF LIST" << std::endl;
	pos = run(&temp);
	//std::cout << "END OF LIST" << std::endl;
	return pos + 1;
}

bool decode::IsVedio(const std::string* str){
	std::string vedio[10] = {"avi" ,"rmvb" ,"rm" ,"mpg" ,"mpeg" ,"wmv" ,"mp4" ,"mkv" ,"ISO" ,"wma"};
		 
	for(int i = 0;i < 10;i++){
		if(str->find(vedio[i]) != (-1)){
			return true;
		}
	}
	return false;
}
