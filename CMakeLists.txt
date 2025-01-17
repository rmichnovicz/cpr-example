cmake_minimum_required(VERSION 2.8.7)
project(cpr-example)

if(NOT ${CMAKE_VERSION} LESS 3.2)
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
else()
    message(STATUS "Checking compiler flags for C++11 support.")
    # Set C++11 support flags for various compilers
    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
    check_cxx_compiler_flag("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
    if(COMPILER_SUPPORTS_CXX11)
        message(STATUS "C++11 is supported.")
        if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -stdlib=libc++")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
        endif()
    elseif(COMPILER_SUPPORTS_CXX0X)
        message(STATUS "C++0x is supported.")
        if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -stdlib=libc++")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
        endif()
    else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
    endif()
endif()

add_subdirectory(opt)
find_package(Boost COMPONENTS iostreams REQUIRED)

add_executable(example example.cpp Api.cpp Api.h GridfloatReader.cpp GridfloatReader.h)
target_link_libraries(example ${CPR_LIBRARIES})

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)
#set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} $/usr/include/gdal)
#find_package(GDAL REQUIRED)
#include_directories( include ${GDAL_INCLUDE_DIRS})
#message("GDAL DIR: ${GDAL_INCLUDE_DIRS}")
#target_link_libraries( example ${GDAL_LIBRARIES})

target_link_libraries(example ${Boost_LIBRARIES})
include_directories(${CPR_INCLUDE_DIRS} ${JSON_INCLUDE_DIRS})
