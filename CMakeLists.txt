project(SMS)
cmake_minimum_required(VERSION 3.2)

set(CMAKE_C_STANDARD 17)

add_executable(sms main.c)

add_subdirectory(modules)

target_link_libraries(sms console)
target_link_libraries(sms storage)
target_link_libraries(sms student)
target_link_libraries(sms menu)
target_link_libraries(sms path)
target_link_libraries(sms utils)