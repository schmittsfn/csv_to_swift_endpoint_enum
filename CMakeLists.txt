cmake_minimum_required(VERSION 3.12)
project(SwiftEndpointEnumGenerator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(csv_to_swift_endpoint_enum csv_to_swift_endpoint_enum.cpp)
