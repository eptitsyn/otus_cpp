#include "lib.h"

#include "gtest/gtest.h"

TEST(VersionTest, GreaterThanZero){
		EXPECT_GT(version(), 0);
}


