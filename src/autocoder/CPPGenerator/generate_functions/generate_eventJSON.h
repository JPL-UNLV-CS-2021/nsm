#ifndef QSM_GENERATE_eventJSON_H
#define QSM_GENERATE_eventJSON_H


#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <unordered_set>
#include "../JSON/json.hpp"
using namespace std;
void generate_eventJSON(nlohmann::json j);

#endif