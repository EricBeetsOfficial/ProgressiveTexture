#include <gtest/gtest.h>

#include <Log.h>
#include <Utils.h>

#include <set>

void Randomize(int count, int minValue, int maxValue)
{
    std::multiset<int> values;
    for (int i = 0; i < count; ++i)
    {
        values.insert(Utils::Random(minValue, maxValue));
    }
    EXPECT_EQ(count, values.size());
    int max = *std::max_element(values.begin(), values.end());
    int min = *std::min_element(values.begin(), values.end());
    EXPECT_TRUE(max < maxValue);
    EXPECT_TRUE(min >= minValue);
    // for (auto value: values) DEBUG(value);
}

TEST(TestUtils, Random)
{
    Utils::InitRand();
    Randomize(10, 0, 10);
    Randomize(10, 0, 100);
    Randomize(2, 0, 5);
    Randomize(30, -100, 10);
}

TEST(TestUtils, PowerOf2)
{
    EXPECT_TRUE(Utils::IsPowerOf2(0));
    EXPECT_TRUE(Utils::IsPowerOf2(1));
    EXPECT_TRUE(Utils::IsPowerOf2(16));
    EXPECT_TRUE(Utils::IsPowerOf2(32));
    EXPECT_TRUE(Utils::IsPowerOf2(4096));
    EXPECT_FALSE(Utils::IsPowerOf2(3));
    EXPECT_FALSE(Utils::IsPowerOf2(-3));
    EXPECT_FALSE(Utils::IsPowerOf2(1023));

    EXPECT_EQ(Utils::HighestPowerOf2(13), 16);
    EXPECT_EQ(Utils::HighestPowerOf2(24), 32);
    EXPECT_EQ(Utils::HighestPowerOf2(33), 64);
    EXPECT_EQ(Utils::HighestPowerOf2(511), 512);
    EXPECT_EQ(Utils::HighestPowerOf2(670), 1024);

    EXPECT_EQ(Utils::SmallestPowerOf2(13), 8);
    EXPECT_EQ(Utils::SmallestPowerOf2(24), 16);
    EXPECT_EQ(Utils::SmallestPowerOf2(33), 32);
    EXPECT_EQ(Utils::SmallestPowerOf2(511), 256);
    EXPECT_EQ(Utils::SmallestPowerOf2(670), 512);

    EXPECT_EQ(Utils::ClosestPowerOf2(13), 16);
    EXPECT_EQ(Utils::ClosestPowerOf2(24), 32);
    EXPECT_EQ(Utils::ClosestPowerOf2(33), 32);
    EXPECT_EQ(Utils::ClosestPowerOf2(511), 512);
    EXPECT_EQ(Utils::ClosestPowerOf2(670), 512);
}