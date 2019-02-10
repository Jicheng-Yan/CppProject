file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testBubbleSort ${SRCS})

TARGET_LINK_LIBRARIES(testBubbleSort
    libbubblesort
    gtest
    gmock
)

# convenience target for running only the unit tests
add_custom_target(unitBubbleSort
    #this way we can use faux data from /test dir (if we have any):
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/test
    COMMAND $<TARGET_FILE:testBubbleSort>
    DEPENDS testBubbleSort)
