cmake_minimum_required(VERSION 3.6)
project(tnp)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(ICONV REQUIRED)

set(Boost_USE_MULTITHREADED ON)
find_package(Boost 1.62.0 COMPONENTS graph)

MESSAGE(STATUS "Boost: " ${Boost_FOUND})

include_directories(
        ${tnp_SOURCE_DIR}
        ${ICONV_INCLUDE_DIR}
        ${Boost_INCLUDE_DIRS}
)

set(SOURCE_FILES main.cpp tn_network/tn_struct.h file_utils/Outbuff.cpp file_utils/Outbuff.h file_utils/ConverterException.h file_utils/Converter.cpp file_utils/Converter.h file_utils/utils.hpp graph/BaseGraph.cpp graph/BaseGraph.h tn_network/tn_struct.cpp)
add_executable(tnp ${SOURCE_FILES})
target_link_libraries(tnp ${ICONV_LIBRARY} ${Boost_LIBRARIES})