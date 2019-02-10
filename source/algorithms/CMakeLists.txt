set(libbubblesort_SRCS
    bubbleSort.h
    bubbleSort.cpp
)

# Declare the library
add_library(libbubblesort STATIC
    ${libbubblesort_SRCS}
)

# Specify here the include directories exported
# by this library
target_include_directories(libbubblesort PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)


