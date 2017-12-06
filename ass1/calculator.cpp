#include <iostream>
#include <fstream>
#include <iomanip>
#include <stack>
#include <cmath>
#include <vector>
#include <queue>


//functions
void parser(std::vector<std::string> vec,std::stack<std::string>& buff);
void calculation(std::stack<std::string>& buff,std::string s);
void sqrt(std::stack<std::string>& buff);
void reverse(std::stack<std::string>& buff);
std::vector<std::string>::iterator repeat(std::stack<std::string>& buff, std::vector<std::string>::iterator token);
bool isInt(std::string num);

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

//parser function to handle operation
void parser(std::vector<std::string> vec,std::stack<std::string>& buff){
	for(auto token = vec.begin(); token != vec.end(); ++token) {
		if(isdigit((*token)[0])||isdigit((*token)[1])||isdigit((*token)[2])){
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

//function to handle add, sub,mult, div 
void calculation(std::stack<std::string>& buff,std::string s){
	std::string num1 = buff.top();
	buff.pop();
	std::string num2 = buff.top();
	buff.pop();
	double result = 0.0;
	std::string operand = "";

	//getting operand and result
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
		//check operand if is valid
	   if(std::stod(num2)==0){
	      std::cout<<"Invid operand\n";
	      exit (EXIT_FAILURE);
      }
		result=std::stod(num1)/std::stod(num2);
		operand=" / ";
	}

	//formating output.
	if(!isInt(num1)&& isInt(num2)){
		std::cout << std::stod(num1) << operand << num2 << " = " << result<<"\n";
		buff.push(std::to_string(result));	
	} else if(isInt(num1)&& !isInt(num2)) {
		std::cout << num1 << operand << std::stod(num2) << " = " << result<<"\n";
		buff.push(std::to_string(result));			
	} else if(!isInt(num1)&& !isInt(num2)) {
		std::cout << std::stod(num1) << operand << std::stod(num2) << " = " << result<<"\n";
		buff.push(std::to_string(result));	
	} else{
		std::cout << num1 << operand << num2 << " = " << static_cast <int>(result)<<"\n";
		buff.push(std::to_string(static_cast <int>(result)));
	}
}

//sqrt function
void sqrt(std::stack<std::string>& buff){
	std::string num = buff.top();
	buff.pop();
	//check operand if is valid
	if(std::stod(num)<0){
	   std::cout<<"Invalid input\n";
	   exit (EXIT_FAILURE);
	}
	double result = sqrt(std::stod(num));
	if(num.find('.') != std::string::npos){
		std::cout << "sqrt " << std::stod(num) <<" = " << result << "\n";
		buff.push(std::to_string(result));	
	} else {
		std::cout << "sqrt " << num <<" = " << static_cast <int>(result) << "\n";
		buff.push(std::to_string(static_cast <int>(result)));		
	}
}

//solve the repeat operation recursivly
std::vector<std::string>::iterator repeat(std::stack<std::string>& buff, std::vector<std::string>::iterator token){
	int repeattimes = std::stoi(buff.top());
	//check operand if is valid
	if(repeattimes<0){
	   std::cout<<"Invid operand\n";
	   exit (EXIT_FAILURE);
	}
	buff.pop();
	int startcount = 1;
	int endcount =0;
	std::vector<std::string> tokens;
	token++;
	tokens.push_back(*token);
	//find the ending instrustion for repeat
	//nested repeated handled 
	while(startcount != endcount){
		token++;
		tokens.push_back(*token);
		if(*token=="repeat"){
			startcount++;
		} else if(*token=="endrepeat"){
			endcount++;
		}
	}
	//recursion
	for(;repeattimes > 0; --repeattimes){
		parser(tokens,buff);
	}
	return token++;

}

//reversing the stack by push the number of elements to 
//a queue and that push it into the stack one by one again
void reverse(std::stack<std::string>& buff){
	int i =0;
	int nnum = std::stoi(buff.top());
	//check operand if is valid
	if(nnum<0){
	   std::cout<<"Invid operand\n";
	   exit (EXIT_FAILURE);
	}
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

//helper function to check if is int or double 
bool isInt(std::string num){
	if(num.find('.') != std::string::npos){
		return false;
	} 
	return true;
}
