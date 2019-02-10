//#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do
                          // this in one cpp file
//#include "catch.hpp"
#include "SomeClass.h"
#include "gtest/gtest.h"
//#include <vector>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(sameclass, set) {
    SomeClass some;
    some.set(5);
    ASSERT_EQ(some.get(), 5);
}


