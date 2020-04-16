#include "matrix.cpp"

#include "gtest/gtest.h"


TEST(Matrixtest, operatorset){
	Matrix<int, -1> matrix;
	matrix[1][1] = -1;
	EXPECT_EQ(matrix[1][1], -1);
	EXPECT_EQ(matrix.size(), 0);
	matrix[100][100] = 314;
	EXPECT_EQ(matrix[100][100], 314);
	EXPECT_EQ(matrix.size(), 1);
}

TEST(Matrixtest, tasktest){
	Matrix<int, 0> matrix;
	for(int i = 0; i < 10; ++i){
		matrix[i][i] = i;
	}
	for(int i = 0; i < 10; ++i){
		matrix[i][9 - i] = 9 - i;
	}
	EXPECT_EQ(matrix.size(), 18);
}
