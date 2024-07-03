#include <gtest/gtest.h>

#if 1
// Demonstrate some basic assertions.
TEST(HelloTest, Test01)
{
  // Expect two strings not to be equal.
  // EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST(HelloTest, Test02)
{
  // Expect two strings not to be equal.
   EXPECT_STRNE("Pouet", "Pouett");
  // // Expect equality.
  // EXPECT_EQ(7 * 5, 42);
}

TEST(HelloTest, Test03) {
  // GTEST_MEMLEAK_DETECTOR_APPEND_LISTENER;

    // Do memory leak detection for this test
    int* dummy = new int[16];
    delete []dummy;
    //Your test code
}
#endif
