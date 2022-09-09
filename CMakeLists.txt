cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 17) 
project(ttt) 

file(GLOB SOURCES
  src/*
)

#add_executable(ttt src/main.cpp)
add_executable( ttt ${SOURCES})
