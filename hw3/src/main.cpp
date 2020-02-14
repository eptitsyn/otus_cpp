#include "myallocator.hpp"
#include "myvector.hpp"

#include <iostream>
#include <map>

size_t factorial(int i){
	size_t result = 1;
	while (i > 1){
		result *= i--;
	}
	return result;
}

int main(){
	{
		std::map<int, std::size_t, std::less<int>, myallocator< std::pair<const int, std::size_t>> > map1;
		for(int i = 0; i < 10; ++i){
			map1[i]= factorial(i);
		}
	}
	{
		std::map<int, std::size_t, std::less<int>, myallocator< std::pair<const int, std::size_t>, 10>> mymap;

		for(int i = 0; i < 10; ++i){
			mymap[i]= factorial(i);
		}

		for(auto& [key, value] : mymap){
			std::cout << key << " : " << value << std::endl;
		}
	}
	std::cout << "my vector" << std::endl;

	{	
		myvector<int> mvec;
		for(int i = 0; i < 10; ++i){
			mvec.push_back(i);
		}

		for(auto &i : mvec){
			std::cout << i << std::endl;
		}
	
		mvec = myvector<int, myallocator<int,10>>();
		for(int i = 0; i < 10; ++i){
			mvec.push_back(i);
		}
		for(auto &i : mvec){
			std::cout << i << std::endl;
		}
	}

	return 0;
}