#include "generate_cmake.h"
#include <filesystem>
#include <vector>
using json = nlohmann::json;
using std::filesystem::current_path;

void generate_cmake(json j) { //Generate CMakeLists.txt for code compilation
    ofstream cmake_file;
    cmake_file.open("Output_Files\\generated_code\\CMakeLists.txt"); // Open the created source file to write into

    vector<string> statenames;
    //Get states from json
    for (const auto& stateChartitem : j.items()) {
        if (stateChartitem.key() == "states") {
            for (const auto& state : stateChartitem.value()) {
                for (const auto& stateMember : state.items()) {
                    if (stateMember.key() == "name") {
                        statenames.push_back(stateMember.value());
                    }
                }
            }
        }
    }


    string HSM_name("GeneratedHSM");

    cmake_file << "cmake_minimum_required(VERSION 3.17)\n"
                  "project(QSM)\n"
                  "\n"
                  "set(CMAKE_CXX_STANDARD 14)\n"
                  "\n"
                  "add_executable(" << HSM_name << " \n"
                  << HSM_name << ".cpp \n"
                  "HSMState/HSMState.h \n"
                  "HSMState/HSMState.cpp \n"
                  "UserObjects/bsp.cpp \n"
                  "UserObjects/bsp.hpp \n"
                  "HSM/HSM.h\n"
                  "HSM/HSM.cpp\n"
                  "Event/Event.h\n"
                  "Event/Event.cpp\n";

    for (int i = 0; i < statenames.size(); i++) {
            cmake_file << statenames[i] << "/" << statenames[i] << ".h" << "\n" 
                       << statenames[i] << "/" << statenames[i] << ".cpp" << "\n";
    }
    cmake_file << ")\n";

    cmake_file.close();
}