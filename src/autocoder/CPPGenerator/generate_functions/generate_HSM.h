#ifndef QSM_GENERATE_HSM_H
#define QSM_GENERATE_HSM_H


#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>
#include "../JSON/json.hpp"

using namespace std;
void generate_HSM(nlohmann::json j);
#endif //QSM_GENERATE_STATES_H