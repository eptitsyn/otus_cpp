#include "interpreter.hpp"

#include "gtest/gtest.h"

TEST(bulk, test1){
	{
		testing::internal::CaptureStdout();
		Interpreter subj(3);
		ostreamObserver coutObserver(&subj, std::cout);

		subj.addString("cmd1");
		subj.addString("cmd2");
		subj.addString("cmd3");

		std::string output = testing::internal::GetCapturedStdout();
		EXPECT_EQ("bulk: cmd1, cmd2, cmd3\n",output);
		testing::internal::CaptureStdout();

		subj.addString("cmd4");
		subj.addString("cmd5");
	}

	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ("bulk: cmd4, cmd5\n",output);
};

TEST(bulk, test2){
	{
		testing::internal::CaptureStdout();
		Interpreter subj(3);
		ostreamObserver coutObserver(&subj, std::cout);

		subj.addString("cmd1");
		subj.addString("cmd2");
		subj.addString("cmd3");

		std::string output = testing::internal::GetCapturedStdout();
		testing::internal::CaptureStdout();
		EXPECT_EQ("bulk: cmd1, cmd2, cmd3\n",output);

		subj.addString("{");
		subj.addString("cmd4");
		subj.addString("cmd5");
		subj.addString("cmd6");
		subj.addString("cmd7");
		subj.addString("}");
	}

	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ("bulk: cmd4, cmd5, cmd6, cmd7\n",output);
};

TEST(bulk, test3){
	{
		testing::internal::CaptureStdout();
		Interpreter subj(3);
		ostreamObserver coutObserver(&subj, std::cout);		
		subj.addString("{");
		subj.addString("cmd1");
		subj.addString("cmd2");
		subj.addString("{");
		subj.addString("cmd3");
		subj.addString("cmd4");
		subj.addString("}");
		subj.addString("cmd5");
		subj.addString("cmd6");
		subj.addString("}");
		
	}
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ("bulk: cmd1, cmd2, cmd3, cmd4, cmd5, cmd6\n",output);
};

TEST(bulk, test4){
	testing::internal::CaptureStdout();
	{
		Interpreter subj(3);
		ostreamObserver coutObserver(&subj, std::cout);

		subj.addString("cmd1");
		subj.addString("cmd2");
		subj.addString("cmd3");
		subj.addString("{");
		subj.addString("cmd4");
		subj.addString("cmd5");
		subj.addString("cmd6");
		subj.addString("cmd7");
	}
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ("bulk: cmd1, cmd2, cmd3\n",output);
};