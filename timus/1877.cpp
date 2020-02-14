#include <iostream>

int main(){
	int a,b;
	std::cin >> a >> b;
	const char * result = (a%2 == 0 || b%2 == 1)? "yes" : "no";
	std::cout <<  result << std::endl;
	return 0;
}