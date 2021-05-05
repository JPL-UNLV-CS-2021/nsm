cmake_minimum_required(VERSION 3.17)
project(QSM)

set(CMAKE_CXX_STANDARD 14)

add_library(
        HSM/State/HSMState.h
        HSM/State/HSMState.cpp
        HSM/StateMachine/HSM.h
        HSM/StateMachine/HSM.cpp
)

#add_executable(
#    src/State/HSMState.h
#    src/State/HSMState.cpp
#    src/StateMachine/HSM.h
#    src/StateMachine/HSM.cpp
#)