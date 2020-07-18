cmake_minimum_required(VERSION 3.16)

project(Chat_Server)

include_directories(include ../Shared)

add_executable(server src/server.cpp src/main.cpp)