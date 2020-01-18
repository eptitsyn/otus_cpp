#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

int main(){
	vector<unsigned long long int> nums;
	string tmp;
	while(getline(cin, tmp)) {
        stringstream ss(tmp);
        unsigned long long int ti;
        while(ss >> ti) 
            nums.push_back(ti);
        //do stuff with nums
    }

    for(auto i = nums.rbegin(); i != nums.rend(); ++i){
    	printf("%.4f\n", sqrt(*i));
    }
	return 0;
}