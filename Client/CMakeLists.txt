cmake_minimum_required(VERSION 3.16)

project(Chat_Client)

include_directories(include ../Shared)

add_executable(Client src/client.cpp)