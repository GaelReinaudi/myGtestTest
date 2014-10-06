// unittestPrice.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <map>
//int _tmain(int argc, _TCHAR* argv[])
//{
//	return 0;
//}


#include "gtest/gtest.h"
#include "Price.h"

TEST(testMath, zero)
{
	Price p(0.0);
	EXPECT_EQ(p.decomp.floor, 0);
	EXPECT_EQ(p.decomp.frac, 0);
}

TEST(testMath, decompositionThousand)
{
	for (double d = -1000.0; d <= 1000.0 + 1e-9; d += 0.001)
	{
		Price p(d);
		EXPECT_EQ(p.decomp.floor, floor(d + 1e-10));
		unsigned short fr = unsigned short((d + 1e-10 - p.decomp.floor) * (1 << 16));
//		fr &= 0xFFFE;
		EXPECT_EQ(p.decomp.frac, fr);
	}
}

TEST(testMath, decompositionMillionNeg)
{
	for (double d = -1000.0; d <= -998.0 + 1e-9; d += 0.000001)
	{
		Price p(d);
		EXPECT_EQ(p.decomp.floor, floor(d + 1e-9));
	}
}
TEST(testMath, decompositionMillionPos)
{
	for (double d = 1000.0; d <= 1002.0 + 1e-9; d += 0.000001)
	{
		Price p(d);
		EXPECT_EQ(p.decomp.floor, floor(d + 1e-9));
	}
}
TEST(testMath, decompositionMillionNull)
{
	for (double d = -1.0; d <= 1.0 + 1e-9; d += 0.000001)
	{
		Price p(d);
		EXPECT_EQ(p.decomp.floor, floor(d + 1e-9));
	}
}

TEST(testMath, fracBins)
{
	std::map<unsigned short, int> allFracBins;
	// for the 0 that is counted once more
	--allFracBins[0];
	int subVal = 1000;
	for (int i = -1000 * subVal; i <= 1000 * subVal; ++i)
	{
		double d = i;
		d /= double(subVal);
		Price p(d);
		++allFracBins[p.decomp.frac];
	}
	for (const auto & p : allFracBins)
	{
		EXPECT_EQ(p.second, 2 * subVal);
	}
}

TEST(testMath, substraction_100)
{
	int subVal = 100;
	for (int i = -1000 * subVal; i <= 1000 * subVal; ++i)
	{
		double d = i;
		d /= double(subVal);
		Price p(d);
		for (int j = -1000 * subVal; j <= 1000 * subVal; ++j)
		{
			double d2 = j;
			d2 /= double(subVal);
			Price p2(d2);
			double sub = d - d2;
			Price psub(sub);
			//EXPECT_EQ(psub.i, (p - p2).i);
		}
	}
}


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