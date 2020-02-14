#include <iostream>

int main(){
	int k, n;
	std::cin >> k >> n;
	int waiting = 0;
	int t;
	for(int i = 0; i < n; ++i){
		std::cin >> t;
		waiting = std::max(0, waiting+t-k);
	}
	std::cout << waiting << std::endl;
	return 0;
}