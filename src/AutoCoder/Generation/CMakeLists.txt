cmake_minimum_required(VERSION 3.17)
project(QSM)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

add_executable(Generation generate.cpp 
generate_functions/generate_states.h 
generate_functions/generate_states.cpp 
generate_functions/generate_states.h 
generate_functions/generate_main.cpp 
generate_functions/generate_main.h 
generate_functions/generate_cmake.h 
generate_functions/generate_cmake.cpp 
generate_functions/generate_HSMState.h 
generate_functions/generate_HSMState.cpp 
generate_functions/generate_HSM.h 
generate_functions/generate_HSM.cpp
generate_functions/generate_eventJSON.cpp
generate_functions/generate_eventJSON.h
generate_functions/generate_UserObjects.h
generate_functions/generate_UserObjects.cpp
Node/Node.cpp
Node/Node.h 
JSON/json.hpp 
Transition/Transition.h 
Junction/Junction.h 
Variable/Variable.h 
Event/Event.cpp 
Event/Event.h "generate_functions/generate_UserObjects.cpp" "generate_functions/generate_UserObjects.h" "Event/Event.cpp" "Event/Event.h")

