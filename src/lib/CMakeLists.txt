cmake_minimum_required(VERSION 3.17)
project(QSM)

set(CMAKE_CXX_STANDARD 14)

add_library(
        State/HSMState.h
        State/HSMState.cpp
        StateMachine/HSM.h
        StateMachine/HSM.cpp
)

#add_executable(
#    src/State/HSMState.h
#    src/State/HSMState.cpp
#    src/StateMachine/HSM.h
#    src/StateMachine/HSM.cpp
#)