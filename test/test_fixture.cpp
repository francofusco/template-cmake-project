#include <foo/foo.hpp>
#include <gtest/gtest.h>


class MyFixtureTest : public ::testing::Test {
protected:
  MyFixtureTest() : overflow(3, true), limited(3, false) {
    // a default constructor can be provided to initialize objects
  }

  void SetUp() override {
    // initial setup here, in case you do not provide a def.c.tor
  }

  void TearDown() override {
    // code to be executed at exit, if any
  }

  foo::Counter overflow;
  foo::Counter limited;
};


TEST_F(MyFixtureTest, CountersStartAtZero) {
  EXPECT_EQ(0, overflow.currentCount());
  EXPECT_EQ(0, limited.currentCount());
}


TEST_F(MyFixtureTest, Reset) {
  overflow.countOnce(); // c = 1
  overflow.countOnce(); // c = 2
  overflow.reset(); // c = 0
  EXPECT_EQ(0, overflow.currentCount());
  limited.countOnce(); // c = 1
  limited.countOnce(); // c = 2
  limited.reset(); // c = 0
  EXPECT_EQ(0, limited.currentCount());
}


TEST_F(MyFixtureTest, OverflowDoesOverflow) {
  overflow.countOnce(); // c = 1
  overflow.countOnce(); // c = 2
  overflow.countOnce(); // c = 3
  overflow.countOnce(); // c = 0
  overflow.countOnce(); // c = 1
  EXPECT_EQ(1, overflow.currentCount());
}


TEST_F(MyFixtureTest, LimitedDoesNotOverflow) {
  limited.countOnce(); // c = 1
  limited.countOnce(); // c = 2
  limited.countOnce(); // c = 3
  limited.countOnce(); // c = 3
  limited.countOnce(); // c = 3
  EXPECT_EQ(3, limited.currentCount());
}


int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
