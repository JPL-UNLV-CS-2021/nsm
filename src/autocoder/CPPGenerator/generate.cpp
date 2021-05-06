#include <iostream>
#include <filesystem>
#include <string>

#include "generate_functions/generate_states.h"
#include "generate_functions//generate_main.h"
#include "generate_functions/generate_cmake.h"
#include "generate_functions/generate_HSMState.h"
#include "generate_functions/generate_HSM.h"
#include "generate_functions/generate_eventJSON.h"
#include "generate_functions/generate_UserObjects.h"
#include "JSON/json.hpp"

using namespace std;
using json = nlohmann::json;
using std::filesystem::current_path;

// Should be passed an argument that is the path to the input file
// The input file should be located in the same directory as the executable
// (or at least referenced to it by the IDE/CMAKE) and should be inside a folder
// called Input_Files
int main (int argc, char* argv[]) {

    filesystem::path root = current_path();
    ifstream JSONFile;

    cout << "\n**********QSM**********\n"
         << "-----------------------"
         << "\n*******AutoCoder*******\n" << endl;

    //// Open the file that contains the state machine data
    JSONFile.open(argv[1]);
    if(!JSONFile.is_open()) {
        cout << "Input file could not be opened" << endl;
        return 0;
    }
    else
        cout << "Input file opened successfully" << endl;

    auto j = json::parse(JSONFile);
    //cout << j.dump() << endl;
    JSONFile.close();
  

    //// Create directory for generated C++ source code
    filesystem::remove_all("Output_Files");
    filesystem::create_directory("Output_Files");
    filesystem::create_directory("Output_Files/generated_code");
    filesystem::create_directory("Output_Files/generated_code/UserObjects");;
    filesystem::create_directory("Output_Files/generated_code/Event");
    filesystem::copy("Event", "Output_Files/generated_code/Event");

    generate_states(j);
    generate_HSM(j);
    generate_main(j);
    generate_HSMState(j);
    generate_cmake(j);
    generate_UserObjects(j);
    generate_eventJSON(j);

    std::cout << "Code Generation Complete!" << endl;

    return 0;
}