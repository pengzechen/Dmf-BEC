#CMake最低版本号要求
cmake_minimum_required(VERSION 3.10.0)

#指定项目名称
project(DmfBridge)

#可以输出中文
if( CMAKE_SYSTEM_NAME STREQUAL "Windows" )
    add_definitions("-fexec-charset=gbk")
endif()

#指定版本信息
set(CMAKE_SYSTEM_VERSION 1)

#指定编译目录
set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)

include_directories(${PROJECT_SOURCE_DIR})
link_directories("${PROJECT_SOURCE_DIR}/lib")

link_libraries("pthread")


file( GLOB main_SRC "*.h" "*.c" )

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")


add_subdirectory("${PROJECT_SOURCE_DIR}/server") 
add_subdirectory("${PROJECT_SOURCE_DIR}/client2") 
add_subdirectory("${PROJECT_SOURCE_DIR}/client1") 

