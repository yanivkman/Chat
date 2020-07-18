cmake_minimum_required(VERSION 3.16)

project(Chat_Client)

include_directories(include ../Shared)

add_executable(client src/client.cpp src/main.cpp)