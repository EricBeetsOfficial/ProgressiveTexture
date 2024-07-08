#include <gtest/gtest.h>

#include <Log.h>
#include <Random.h>

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
    for (auto value: values) DEBUG(value);
}

TEST(TestUtils, Random)
{
    Utils::InitRand();
    Randomize(10, 0, 10);
    Randomize(10, 0, 100);
    Randomize(2, 0, 5);
    Randomize(30, -100, 10);
}
