cmake_minimum_required(VERSION 3.18)
project(sem_Ants_client)

set(CMAKE_CXX_STANDARD 17)

add_executable(sem_Ants_client main.cpp my_socket.cpp my_socket.h)
target_link_libraries(sem_Ants_client wsock32 ws2_32)
#wsock32