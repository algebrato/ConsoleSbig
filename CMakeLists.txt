project(ConsoleSbig)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(./src SRC_LIST)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L /usr/local/lib -L /data/fits/cfitsio/lib/ -lm -lsbigudrv -lcfitsio -lm -lpthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I /usr/include/libusb-1.0/ -I /usr/include/libusb-1.0/ -I /data/fits/cfitsio")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -O2 -g -std=c++11 -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable(${PROJECT_NAME} ${SRC_LIST})
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
	message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()
