#pragma once

#include <vector>
#include <array>
#include <iostream>
#include <tuple>
#include <string>
#include <cstdio>

using namespace std;

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

class ipaddr
{
public:
	explicit ipaddr(string ipstr){
		vector<string> splt = split(ipstr, '.');
		for(int i = 0; i < 4; ++i){
			byte[i] = static_cast<unsigned char>(stoi(splt[i]));
		}	
	}

	bool operator<(const ipaddr& rhs) const{
		return tie(this->byte[0], this->byte[1], this->byte[2], this->byte[3]) < 
			   tie(rhs.byte[0], rhs.byte[1], rhs.byte[2], rhs.byte[3]);
	}

	unsigned char byte[4] = {0,0,0,0};
};

ostream& operator<<(ostream& os, const ipaddr& ip){
    os << +ip.byte[0] << '.' 
    << +ip.byte[1] << '.' 
    << +ip.byte[2] << '.'
    << +ip.byte[3];
    return os;
}

bool byteeq(unsigned char const []){
	return false;
}

template<typename... Args>
bool byteeq(unsigned char const byte[], const unsigned char filter, Args... args){
	if (sizeof...(args ) == 0) 
		return (*byte == filter);
	else
		return (*byte == filter) && byteeq(byte+1, args...);
}

template<typename... Args>
vector<ipaddr> filterip(const vector<ipaddr> &iplist, Args... args){
	vector<ipaddr> result;
	for(auto &i : iplist){
		if(byteeq(i.byte, args...)) 
			result.push_back(i);
	}
	return result;
}

vector<ipaddr> filterip_any(const vector<ipaddr> &iplist, const unsigned char filter){
	vector<ipaddr> result;
	for(auto &i : iplist){
		if (i.byte[0] == filter || 
			i.byte[1] == filter ||
			i.byte[2] == filter ||
			i.byte[3] == filter) 
				result.push_back(i);
	}
	return result;
}