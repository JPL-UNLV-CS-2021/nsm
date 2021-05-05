cmake_minimum_required(VERSION 3.17)
project(QSM)

set(CMAKE_CXX_STANDARD 14)

add_executable(StopLight-StateDesignPattern 
StopLight-StateDesignPattern.cpp 
../HSMState/HSMState.h
HSMState/HSMState.cpp 
HSM/HSM.h
HSM/HSM.cpp
Off/Off.h
Off/Off.cpp
Operational/Operational.h
Operational/Operational.cpp
pedestriansEnabled/pedestriansEnabled.h
pedestriansEnabled/pedestriansEnabled.cpp
pedestriansWalk/pedestriansWalk.h
pedestriansWalk/pedestriansWalk.cpp
pedestriansFlash/pedestriansFlash.h
pedestriansFlash/pedestriansFlash.cpp
vehiclesEnabled/vehiclesEnabled.h
vehiclesEnabled/vehiclesEnabled.cpp
vehiclesGreen/vehiclesGreen.h
vehiclesGreen/vehiclesGreen.cpp
vehiclesGreenInt/vehiclesGreenInt.h
vehiclesGreenInt/vehiclesGreenInt.cpp
vehiclesYellow/vehiclesYellow.h
vehiclesYellow/vehiclesYellow.cpp
)
