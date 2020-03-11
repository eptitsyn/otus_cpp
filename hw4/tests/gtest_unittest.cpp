#include "print_ip.h"

#include "gtest/gtest.h"
#include <sstream>

TEST(ipfiltertest, inttest){
	testing::internal::CaptureStdout();
	print_ip(int(1234));
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ("0.0.4.210\n",output);
};

TEST(ipfiltertest, stringtest){
	testing::internal::CaptureStdout();
	print_ip(std::string("trololo"));
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ("trololo\n",output);
};
