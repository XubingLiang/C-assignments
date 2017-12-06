#include <iostream>
#include <fstream>
#include <iomanip>
#include <stack>
#include <cmath>
#include <vector>
#include <queue>

void parser(std::vector<std::string> vec,std::stack<std::string>& buff);
void calculation(std::stack<std::string>& buff,std::string s);
void sqrt(std::stack<std::string>& buff);
void reverse(std::stack<std::string>& buff);
std::vector<std::string>::iterator repeat(std::stack<std::string>& buff, std::vector<std::string>::iterator token);
int  checktype(std::string num, std::string num2);

int main(int argc, char* argv[]) {

	// setup the print out format for the precision required.
	std::cout.setf(std::ios::fixed,std::ios::floatfield);
	std::cout.precision(3);
	// open the file for reading
	std::ifstream in;
	in.open(argv[1]);
	// string to be read into
	std::string s;
	//vector
	std::vector<std::string> vec;
	//stack to be used
	std::stack<std::string> buff;
	// read the file while we have input.
	while (in >> s) {
		vec.push_back(s);
	}
	in.close();
	parser(vec,buff);
}

void parser(std::vector<std::string> vec,std::stack<std::string>& buff){
	for(auto token = vec.begin(); token != vec.end(); ++token) {
		if(isdigit((*token)[0])){
			buff.push(*token);
		} else if(*token=="reverse"){
			reverse(buff);
		} else if(*token=="repeat"){
			token=repeat(buff,token);
		} else if(*token=="pop"){
			buff.pop();
		} else if(*token== "sqrt"){
			sqrt(buff);
		} else if(*token =="add" || *token=="sub" || *token=="mult" || *token=="div"){
			calculation(buff,*token);
		}
	}

}

void calculation(std::stack<std::string>& buff,std::string s){
	int checkdouble=0;
	std::string num1 = buff.top();
	buff.pop();
	std::string num2 = buff.top();
	buff.pop();
	double result = 0.0;
	std::string operand = "fd";
	if(s=="sub"){
		result=std::stod(num1) - std::stod(num2);
		operand=" - ";
	} else if(s=="add"){
		result=std::stod(num1) + std::stod(num2);
		operand=" + ";
	} else if(s=="mult"){
		result=std::stod(num1) * std::stod(num2);
		operand=" * ";
	}else if (s == "div"){
		result=std::stod(num1)/std::stod(num2);
		operand=" / ";
	}

	checkdouble=checktype(num1,num2);
	if(checkdouble == 1){
		std::cout << std::stod(num1) << operand << num2 << " = " << result<<"\n";
		buff.push(std::to_string(result));	
	} else if(checkdouble == 2) {
		std::cout << num1 << operand << std::stod(num2) << " = " << result<<"\n";
		buff.push(std::to_string(result));			
	} else {
		std::cout << num1 << operand << num2 << " = " << int(result)<<"\n";
		buff.push(std::to_string(int(result)));
	}

}


void sqrt(std::stack<std::string>& buff){
	std::string num = buff.top();
	buff.pop();
	double result = sqrt(std::stod(num));
	if(num.find('.') != std::string::npos){
		std::cout << "sqrt " << std::stod(num) <<" = " << result << "\n";
		buff.push(std::to_string(result));	
	} else {
		std::cout << "sqrt " << num <<" = " << int(result) << "\n";
		buff.push(std::to_string(int(result)));		
	}
}

std::vector<std::string>::iterator repeat(std::stack<std::string>& buff, std::vector<std::string>::iterator token){
	int repeattimes = std::stoi(buff.top());
	buff.pop();
	int startcount = 1;
	int endcount =0;
	std::vector<std::string> tokens;
	token++;
	tokens.push_back(*token);
	while(startcount != endcount){
		token++;
		tokens.push_back(*token);
		if(*token=="repeat"){
			startcount++;
		} else if(*token=="endrepeat"){
			endcount++;
		}
	}
	for(;repeattimes > 0; --repeattimes){
		parser(tokens,buff);
	}
	return token++;

}

void reverse(std::stack<std::string>& buff){
	int i =0;
	int nnum = std::stoi(buff.top());
	buff.pop();
	std::queue<std::string> tempque;
	while(i<nnum){
		tempque.push(buff.top());
		buff.pop();
		i++;
	}
	while (!tempque.empty()){
	    buff.push(tempque.front());
	    tempque.pop();
	} 
}

auto getValue(std::string num){
	if(num.find('.') != std::string::npos){
		return std::stod(num);
	}else{
		return std::stoi(num);
	}
}

int checktype(std::string num, std::string num2){
	if(num.find('.') != std::string::npos){
		return 1;
	} else if(num2.find('.') != std::string::npos){
		return 2;
	}
	return 0;
}