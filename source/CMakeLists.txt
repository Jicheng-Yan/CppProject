include(cleanCppExtensions)

# configure version.cpp.in with selected version
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/version.cpp.in"
  "${CMAKE_CURRENT_BINARY_DIR}/version.cpp"
  )
# If you want to have date and time of the build, your targets has to depend on this.
# This will force recompilation of version.o and thus forcing gcc to update __DATE__ macro.
add_custom_target(versionFileTouchForRebuild
    COMMAND ${CMAKE_COMMAND} -E touch "${CMAKE_CURRENT_BINARY_DIR}/version.cpp")


#------------------------------------------------------------------------------
# Libraries dependencies
find_package (Threads REQUIRED) #threading
find_package (gflags REQUIRED)
include_directories (${gflags_INCLUDE_DIR})

#------------------------------------------------------------------------------
# By using macro to add common dependencies you can avoid repetition when you have
# multiple binaries.
# Use with `addCommonDependencies(exampleApp)`
# macro(addCommonDependencies TARGET)
#     add_dependencies(${TARGET} versionFileTouchForRebuild) # We want precise time of build in version
#     target_include_directories(${TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
#     target_link_libraries (${TARGET} PRIVATE ${CMAKE_THREAD_LIBS_INIT})
#     target_compile_definitions(${TARGET} PRIVATE -DSOME_DEFINE)
# endmacro()

#-------------------------------------------------------------------------------
# exampleApp executable setup
#set(ICON_RESOURCE "")
#if(WIN32) #windows icon resource file, provided from /packaging directory
#    set(ICON_RESOURCE "${PROJECT_BINARY_DIR}/exampleApp.icon.rc")
#elseif (APPLE) #osx icon ressource file, provided from /packaging directory
#    set(ICON_RESOURCE "${PROJECT_SOURCE_DIR}/packaging/exampleApp.icns")
#endif()

#add_executable(exampleApp MACOSX_BUNDLE
#    ${ICON_RESOURCE}
#    ${CMAKE_CURRENT_BINARY_DIR}/version.cpp
#    SomeClass.cpp
#    SomeClass.h
#    main.cpp)
#add_dependencies(exampleApp versionFileTouchForRebuild) # We want precise time of build in version
#target_include_directories(exampleApp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
#target_include_directories(exampleApp SYSTEM PRIVATE ${EXTERNAL_SPDLOG_INCLUDE_DIR})
#target_link_libraries (exampleApp PRIVATE ${CMAKE_THREAD_LIBS_INIT} gflags)

# Using macro from cmake/cleanCpppExtensions.cpp included on the top
# Provides exampleApp-run and exampleApp-dbg
#addRunAndDebugTargets(exampleApp)

# short convenience target from cmake/cleanCpppExtensions.cpp
#add_custom_target(run DEPENDS exampleApp-run)

# Manually specified convenience target for running the binary, we use macro
# add_custom_target(exampleApp-run
#     WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin
#     USES_TERMINAL
#     COMMAND ./exampleApp
#     DEPENDS Install_)

# And this would add -DBAR_ENABLE_FEATURE or equivalent to build command
# target_compile_definitions(exampleApp PRIVATE BAR_ENABLE_FEATURE)

# Add compile time definition based on option
# option(OPTION_NAME "description for end user" OFF)
# if(OPTION_NAME)
#     # you can do anything here, eg. setup new optional executable
#     target_compile_definitions(exampleApp PRIVATE DEFINE_NAME)
# endif()

# Add building new shared library
# add_library(exampleLibrary SHARED ${LIBRARY_SOURCES})
# target_link_libraries (exampleLibrary ${CMAKE_THREAD_LIBS_INIT})
# set_property(TARGET exampleLibrary PROPERTY CXX_STANDARD 14) # we want C++14

# How to include and link OpenGL and GLUT libraries
# find_package(OpenGL REQUIRED)
# find_package(GLUT REQUIRED)
# target_include_directories(exampleApp SYSTEM ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} )
# target_link_libraries(exampleApp ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )


enable_testing()

add_subdirectory(main)
add_subdirectory(libfoo)
add_subdirectory(libbar)
add_subdirectory(algorithms)
add_subdirectory(design-patterns)
add_subdirectory(unittest)

#-------------------------------------------------------------------------------
# Copy MINGW needed libraries for building on windows
#if(MINGW)
#    message(STATUS "MinGW detected")
#    get_filename_component(GCC_PATH ${CMAKE_C_COMPILER} PATH)
#    if(${GCC_PATH} MATCHES "mingw64/bin")
#        set(libgcc "libgcc_s_seh-1.dll") #64bit
#        message(STATUS "  64bit dlls is building")
#    else()
#        set(libgcc "libgcc_s_dw2-1.dll") #32bit
#        message(STATUS "  32bit dlls is building")
#    endif()

#    install(FILES ${GCC_PATH}/${libgcc}
#        ${GCC_PATH}/libwinpthread-1.dll
#        ${GCC_PATH}/libstdc++-6.dll
#        DESTINATION ./bin/
#    )
#endif(MINGW)


#------------------------------------------------------------------------------
# Other MISC targets

# Adds misc targets: format, cppcheck, tidy, see cmake/cleanCppExtensions.cmake
#addMiscTargets()


