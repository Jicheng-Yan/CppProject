#include <stdio.h>
#include <string.h>

#include "bubbleSort.h"
#include "testBubbleSort.h"




BubbleSortTest::BubbleSortTest() {}

BubbleSortTest::~BubbleSortTest() {}

void BubbleSortTest::SetUp() {}

void BubbleSortTest::TearDown() {}

TEST_F(BubbleSortTest, sort) {
    int arrayInput[] = {95, 45, 48, 98, 485, 65};
    int arrayOutput[] = { 45, 48,  65,  95, 98, 485};
    int n = sizeof(arrayInput)/sizeof(arrayInput[0]);

    //std::cout << "Before Bubble Sort :" << std::endl;
    //printArray(arrayInput, n);

    bubbleSort(arrayInput, n);
    EXPECT_TRUE( 0 == memcmp( arrayInput, arrayOutput, sizeof(arrayInput) ) );
    //std::cout << "After Bubble Sort :" << std::endl;
    //printArray(arrayInput, n);
    //for (int i = 0; i < n; ++n) {
    //    EXPECT_EQ(arrayInput[i], arrayOutput[i]);
    //}
}


