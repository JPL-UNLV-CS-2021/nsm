cmake_minimum_required(VERSION 3.17)
project(QSM)

set(CMAKE_CXX_STANDARD 14)

add_executable(GeneratedHSM 
GeneratedHSM.cpp 
HSMState/HSMState.h 
HSMState/HSMState.cpp 
UserObjects/bsp.cpp 
UserObjects/bsp.hpp 
HSM/HSM.h
HSM/HSM.cpp
Event/Event.h
Event/Event.cpp
off/off.h
off/off.cpp
on/on.h
on/on.cpp
ModeZ/ModeZ.h
ModeZ/ModeZ.cpp
ModeY/ModeY.h
ModeY/ModeY.cpp
ModeX/ModeX.h
ModeX/ModeX.cpp
)
