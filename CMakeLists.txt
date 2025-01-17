cmake_minimum_required(VERSION 3.24)
project(AeroPhysicalEngine)

set(CMAKE_CXX_STANDARD 17)
#link_directories(${PROJECT_SOURCE_DIR}/lib)
add_executable(AeroPhysicalEngine APEmain.cpp)
target_link_libraries(${PROJECT_NAME} libeasyx.a)