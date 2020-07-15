cmake_minimum_required(VERSION 3.16)

project(Chat_Server)

include_directories(include ../Shared)

add_executable(Server src/server.cpp)