set(libfactory_SRCS
    factory.cpp
)

# Declare the library
add_library(libfactory STATIC
    ${libfactory_SRCS}
)

# Specify here the include directories exported
# by this library
target_include_directories(libfactory PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)


