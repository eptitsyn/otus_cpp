#include "ip_filter_lib.cpp"

#include "gtest/gtest.h"
#include <sstream>

struct ipfiltertest : testing::Test{
	vector<ipaddr> ips;
	ipfiltertest(){
		ips.push_back(ipaddr("1.1.1.1"));
		ips.push_back(ipaddr("2.2.2.2"));	
	}
};

TEST_F(ipfiltertest, filtertest){
	auto tmp = filterip(ips, 1);
	ostringstream os;
	os << tmp.front();
	EXPECT_EQ("1.1.1.1",os.str());
};

