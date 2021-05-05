#ifndef QSM_GENERATE_CMAKE_H
#define QSM_GENERATE_CMAKE_H


#include <string>
#include <sstream>
#include <fstream>
#include "../JSON/json.hpp"
using namespace std;
void generate_cmake(nlohmann::json j);

#endif //QSM_GENERATE_CMAKE_H