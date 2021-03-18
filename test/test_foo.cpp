#include <foo/foo.hpp>
#include <gtest/gtest.h>


TEST(MathTest, Factorial) {
  ASSERT_EQ(1, foo::factorial(0));
  ASSERT_EQ(1, foo::factorial(1));
  ASSERT_EQ(2, foo::factorial(2));
  ASSERT_EQ(6, foo::factorial(3));
  ASSERT_EQ(24, foo::factorial(4));
  ASSERT_EQ(120, foo::factorial(5));
  ASSERT_EQ(720, foo::factorial(6));
  ASSERT_EQ(5040, foo::factorial(7));
  ASSERT_EQ(40320, foo::factorial(8));
  ASSERT_EQ(362880, foo::factorial(9));
}


TEST(MathTest, Sign) {
  ASSERT_EQ(0, foo::sign(0));
  for(int i=1; i<10; i++) {
    ASSERT_EQ(1, foo::sign(i));
    ASSERT_EQ(-1, foo::sign(-i));
  }
}


int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
