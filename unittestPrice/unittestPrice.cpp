// unittestPrice.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//int _tmain(int argc, _TCHAR* argv[])
//{
//	return 0;
//}


#include "gtest/gtest.h"
#include "Price.h"

TEST(testMath, decompositionThousand)
{
	for (double d = -1000.0; d <= 1000.0; d += 0.001)
	{
		Price p(d);
		EXPECT_EQ(p.decomp.floor, floor(d + 1e-10));
		EXPECT_EQ(p.decomp.frac,   unsigned short((d + 1e-10 - p.decomp.floor) * (1 << 16)));
	}
}

TEST(testMath, decompositionMillionNeg)
{
	for (double d = -1000.0; d <= -998.0; d += 0.000001)
	{
		Price p(d);
		EXPECT_EQ(p.decomp.floor, floor(d + 1e-9));
	}
}
TEST(testMath, decompositionMillionPos)
{
	for (double d = 1000.0; d <= 1002.0; d += 0.000001)
	{
		Price p(d);
		EXPECT_EQ(p.decomp.floor, floor(d + 1e-9));
	}
}
TEST(testMath, decompositionMillionNull)
{
	for (double d = -1.0; d <= 1.0; d += 0.000001)
	{
		Price p(d);
		EXPECT_EQ(p.decomp.floor, floor(d + 1e-9));
	}
}

//TEST(testMath, myCubeTest)
//{
//	Price p1(121.2500);
//	Price p2(122.7500);
//
//	ps = p1 + p2;
//	EXPECT_EQ(ps.toDouble(), 244.0000);
//}


/* Test No. 2
TEST(testCalc, MySecondTest)
{
...
}
*/

int _tmain(int argc, _TCHAR* argv[])
{
	/*The method is initializes the Google framework and must be called before RUN_ALL_TESTS */
	::testing::InitGoogleTest(&argc, argv);

	/*RUN_ALL_TESTS automatically detects and runs all the tests defined using the TEST macro.
	It's must be called only once in the code because multiple calls lead to conflicts and,
	therefore, are not supported.
	*/
	return RUN_ALL_TESTS();
}