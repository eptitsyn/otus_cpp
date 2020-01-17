#include "ip_filter_lib.h"

#include <vector>
#include <string>
#include <cstdio>

using namespace std;

int main(){
	try {
		vector<ipaddr> ips;
		for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ips.push_back(ipaddr(v.at(0)));
        }
		sort(ips.rbegin(), ips.rend());

		//output #1
		for(auto &i : ips){
			cout << i << endl;
		}

		auto fips = filterip(ips, 1);

		//output #2
		for(auto &i : fips){
			cout << i << endl;
		}

		auto f2ips = filterip(ips, 46, 70);

		//output #3
		for(auto &i : f2ips){
			cout << i << endl;
		}

		auto f3ips = filterip_any(ips, 46);

		//output #4
		for(auto &i : f3ips){
			cout << i << endl;
		}
	}     
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
	return 0;
}