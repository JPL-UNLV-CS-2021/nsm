#include "generate_HSMState.h"
#include <vector>
using json = nlohmann::json;
using std::filesystem::current_path;

void generate_HSMState(json j) {


    string temp;
    vector<string> actionSet;

    for (const auto& stateChartitem : j.items()) {


        if (stateChartitem.key() == "events") {
            for (const auto& e : stateChartitem.value()) {
                actionSet.push_back(e);
            }
        }
    }

    //ACTIONSET NOW HOLDS LIST OF ALL ACTIONS


    string source;
    string header;
    std::filesystem::create_directory("Output_Files/generated_code/HSMState");
    source = "Output_Files/generated_code/HSMState/HSMState.cpp";
    header = "Output_Files/generated_code/HSMState/HSMState.h";
    ofstream source_file, header_file;

    source_file.open(source);
    header_file.open(header);

    //generate HSMState.cpp (easy one)
    source_file << "#include \"HSMState.h\"\n"
                << "#include <thread>\n"
                << "#include <chrono>\n"
                << "\n"
                << "using namespace std;\n"
                << "\n"
                << "HSMState::HSMState() {\n"
                << "}\n"
                << "\n"
                << "void HSMState::ChangeState(HSM* t, HSMState* s) {\n"
                << "    t->ChangeState(s);\n"
                << "}\n"
                << "std::string stateName;\n"
                << "\n";


    //generate HSMState.h (hard one >.<)
    header_file << "#ifndef HSMState_\n"
                << "#define HSMState_\n"
                << "\n"
                << "#include \"../HSM/HSM.h\"\n"
                << "#include <iostream>\n"
                << "#include <thread>\n"
                << "class HSM;\n"
                << "\n"
                << "class HSMState {\n"
                << "public: \n"
                << "    HSMState();\n"
                << "\n";
    
    //virtual function defs start
    for(const string& x:actionSet) {
        header_file << "    virtual void " << x << "() {\n"
                    << "        std::cout << \"" << x << " Unhandled. Logging..\" << std::endl;\n"
                    << "    }\n";
    }
    //virtual function defs end

    header_file << "\n"
                << "    std::string stateName;\n"
                << "\n"
                << "    virtual void Entry() = 0;\n"
                << "    virtual void Exit() = 0;\n"
                << "\n"
                << "    HSM* _context;\n"
                << "\n"
                << "    //Used for exit/enter call stack\n"
                << "    HSMState* _parent;\n"
                << "    int level = -1;\n"
                << "\n"
                << "protected:\n"
                << "    void ChangeState(HSM*, HSMState*);\n"
                << "};\n"
                << "\n"
                << "#endif\n"
                << "\n";

    source_file.close();
    header_file.close();
}