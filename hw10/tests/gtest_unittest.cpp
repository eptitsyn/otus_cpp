#include "interpretermt.hpp"
#include "gtest/gtest.h"

#include <sstream>
#include <thread>

//no idea how to test multithread
// TEST(bulk, test1){
// 	std::stringstream ss;
// 	{
		
// 		Interpreter subj(3);
// 		ostreamObserver coutObserver(&subj, ss);

// 		subj.addString("cmd1");
// 		subj.addString("cmd2");
// 		subj.addString("cmd3");

// 		std::this_thread::sleep_for(5s);

// 		EXPECT_EQ("bulk: cmd1, cmd2, cmd3\n", ss.str());
		

// 		subj.addString("cmd4");
// 		subj.addString("cmd5");
// 	}
// 	std::this_thread::sleep_for(1s);

// 	EXPECT_EQ("bulk: cmd4, cmd5\n", ss.str());
// };

// TEST(bulk, test2){
// 	{
// 		testing::internal::CaptureStdout();
// 		Interpreter subj(3);
// 		ostreamObserver coutObserver(&subj, std::cout);

// 		subj.addString("cmd1");
// 		subj.addString("cmd2");
// 		subj.addString("cmd3");

// 		std::this_thread::sleep_for(1s);
// 		std::string output = testing::internal::GetCapturedStdout();
// 		testing::internal::CaptureStdout();
// 		EXPECT_EQ("bulk: cmd1, cmd2, cmd3\n",output);

// 		subj.addString("{");
// 		subj.addString("cmd4");
// 		subj.addString("cmd5");
// 		subj.addString("cmd6");
// 		subj.addString("cmd7");
// 		subj.addString("}");
// 	}

// 	std::this_thread::sleep_for(1s);
// 	std::string output = testing::internal::GetCapturedStdout();
// 	EXPECT_EQ("bulk: cmd4, cmd5, cmd6, cmd7\n",output);
// };

// TEST(bulk, test3){
// 	{
// 		testing::internal::CaptureStdout();
// 		Interpreter subj(3);
// 		ostreamObserver coutObserver(&subj, std::cout);		
// 		subj.addString("{");
// 		subj.addString("cmd1");
// 		subj.addString("cmd2");
// 		subj.addString("{");
// 		subj.addString("cmd3");
// 		subj.addString("cmd4");
// 		subj.addString("}");
// 		subj.addString("cmd5");
// 		subj.addString("cmd6");
// 		subj.addString("}");
		
// 	}

// 	std::this_thread::sleep_for(1s);
// 	std::string output = testing::internal::GetCapturedStdout();
// 	EXPECT_EQ("bulk: cmd1, cmd2, cmd3, cmd4, cmd5, cmd6\n",output);
// };

// TEST(bulk, test4){
// 	testing::internal::CaptureStdout();
// 	{
// 		Interpreter subj(3);
// 		ostreamObserver coutObserver(&subj, std::cout);

// 		subj.addString("cmd1");
// 		subj.addString("cmd2");
// 		subj.addString("cmd3");
// 		subj.addString("{");
// 		subj.addString("cmd4");
// 		subj.addString("cmd5");
// 		subj.addString("cmd6");
// 		subj.addString("cmd7");
// 	}

// 	std::this_thread::sleep_for(1s);
// 	std::string output = testing::internal::GetCapturedStdout();
// 	EXPECT_EQ("bulk: cmd1, cmd2, cmd3\n",output);
// };