cmake_minimum_required(VERSION 3.17)
project(FSM)

set(CMAKE_CXX_STANDARD 14)

add_executable(FSM main.cpp
        LightOffState.cpp LightOffState.h
        LightOnState.cpp LightOnState.h
        Event.cpp Event.h
        StateMachine.cpp StateMachine.h
        State.cpp State.h)
