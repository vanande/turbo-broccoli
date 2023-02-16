cmake_minimum_required(VERSION 3.22)
project(sample_curl C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall")

include_directories(curl/include)
link_directories("curl/lib")
link_libraries(CURL)

add_executable(sample_curl main.c cJSON.c cJSON.h)

target_link_libraries(sample_curl CURL)



