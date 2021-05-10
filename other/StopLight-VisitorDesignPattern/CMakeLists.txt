cmake_minimum_required(VERSION 3.17)
project(QSM)

set(CMAKE_CXX_STANDARD 14)

add_executable(StopLight-VisitorDesignPattern 
StopLight-VisitorDesignPattern.cpp 
global.h
        Abstract/Abstract.h
        Concrete/Concrete.cpp
)
