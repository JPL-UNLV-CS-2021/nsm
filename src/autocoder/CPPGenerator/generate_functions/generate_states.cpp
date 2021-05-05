#include "generate_states.h"
#include <iostream>
#include <vector>
#include "../Transition/Transition.h"
#include "../Junction/Junction.h"
#include <algorithm>

using json = nlohmann::json;
using std::filesystem::current_path;
string handleGuard(string guard);
string handleEntryFunctions(string ef);
void generate_states(json j) { // Generate a .cpp source file and a .h header file for each state


    ////Create output directory and files

    string source;
    string header;
    ofstream source_file, header_file;

    for (const auto& stateChartitem : j.items()) {
        if (stateChartitem.key() == "states") {
            for (const auto& state : stateChartitem.value()){

                string state_name = "";
                string state_parent = "";
                vector<string> entry_functions;
                vector<string> exit_functions;
                vector<Transition> state_transitions;
                Junction junction;

                // Collect data from JSON for state
                for (const auto& stateMember : state.items()) {

                    if (stateMember.key() == "name") {
                        state_name = stateMember.value();
                    }

                    if (stateMember.key() == "parent") {
                        state_parent = stateMember.value();
                    }

                    if (stateMember.key() == "entryFunctions") {
                        for (const auto& entryFunc : stateMember.value()) {
                            string s = entryFunc;
                            entry_functions.push_back(s);
                        }
                    }

                    if (stateMember.key() == "exitFunctions") {
                        for (const auto& exitFunc : stateMember.value()) {
                            string s = exitFunc;
                            entry_functions.push_back(s);
                        }
                    }                    
                    
                    if (stateMember.key() == "transitions") {

                        for (const auto& trans : stateMember.value()) {
                            Transition p;
                            p.trigger = trans["trigger"];
                            p.target = trans["target"];
                            p.action = trans["action"];
                            //Transition p(trans["trigger"], trans.value()["target"], trans["action"]);
                            state_transitions.push_back(p);
                        }
                    }

                    if (stateMember.key() == "junction") {

                        json junc = stateMember.value();

                        Junction p;
                        if (junc.contains("trigger")) {
                            p.trigger = junc["trigger"];
                            p.action = junc["action"];
                            p.guard = junc["guard"];
                            p.iftarget = junc["iftarget"];
                            p.ifaction = junc["ifaction"];
                            p.elsetarget = junc["elsetarget"];
                            p.elseaction = junc["elseaction"];

                        }
    
                        junction = p;
                    }


                }


                //Generate Output Files


                std::filesystem::create_directory("Output_Files/generated_code/" + state_name);
                source = "Output_Files/generated_code/" + state_name + "/" + state_name +  ".cpp";
                header = "Output_Files/generated_code/" + state_name + "/" + state_name + ".h";

                // Open the created source file to write into
                source_file.open(source); 

                //Generate dependencies
                source_file << "#include \"" << state_name << ".h\"\n"
                               "#include \"../HSMState/HSMState.h\"\n"
                               "#include \"../HSM/HSM.h\"\n"
                               "#include \"../UserObjects/bsp.hpp\"\n";

                cout << "Generating " << state_name << endl;
                vector<string> includes;
                for (int i = 0; i < state_transitions.size(); ++i) {
                    source_file << "#include \"../" << state_transitions[i].target << "/" << state_transitions[i].target << ".h\"\n";
                    includes.push_back(state_transitions[i].target);
                }

                if (junction.trigger != "") {
                    if (!(std::find(includes.begin(), includes.end(), junction.iftarget) != includes.end()))
                    {
                        source_file << "#include \"../" + junction.iftarget + "/" << junction.iftarget << ".h\"\n";
                    }
                    if (!(std::find(includes.begin(), includes.end(), junction.elsetarget) != includes.end()))
                    {
                        source_file << "#include \"../" + junction.elsetarget + "/" << junction.elsetarget << ".h\"\n";
                    }
                }



                source_file << "\n#include <iostream>\n"
                    "HSMState * " + state_name + "::_self = NULL; "
                    "\n"
                    "//Constructor\n"
                    "" << state_name << "::" << state_name << "() {\n"
                    "    std::cout << \"" << state_name << " Constructed\" << std::endl;\n"
                    "}\n"

                //Generate Entry Functions
                    "\n//Entry Functions\n"
                    "void " << state_name << "::Entry() {\n"
                    "    std::cout << \"Entered " << state_name << " State\" << std::endl;\n";

                for (int i = 0; i < entry_functions.size(); i++) {
                    source_file << "    " << handleEntryFunctions(entry_functions[i]) << "\n";
                }
                source_file  << "}\n";

                //Generate Exit Functions
                source_file << "\n//Exit Functions\n"
                    "void " << state_name << "::Exit() {\n";

                for (int i = 0; i < exit_functions.size(); i++) {
                    source_file << 
                        "    std::cout << \"" + exit_functions[i] << "\" << std::endl;\n";
                }
                source_file << "    std::cout << \"Exited " << state_name << " State\" << std::endl;\n" << "}\n"
                            
                //Generate Transition Functions

                <<               "\n//Transitions\n";

                for (int i = 0; i < state_transitions.size(); i++) {
                    source_file << "void " << state_name << "::" << state_transitions[i].trigger << "() {\n"
                        << state_transitions[i].action << "\n"
                        << "    HSMState::ChangeState(this->_context, " << state_transitions[i].target << "::Instance());\n"
                        << "}\n";
                }

                //Generate Junction Functions
                if (junction.trigger != "") {
                    source_file << "                \n//Junctions\n\n"
                        "void " << state_name << "::" << junction.trigger << "() {\n\n"
                        "   if(" + handleGuard(junction.guard) + ") {\n"
                        "       " << junction.ifaction <<  "\n"
                        "       HSMState::ChangeState(this->_context, " + junction.iftarget + "::Instance());\n"
                        "   }\n"
                        "   else {\n\n"
                        "       " << junction.elseaction << "\n"
                        "       HSMState::ChangeState(this->_context, " + junction.elsetarget + "::Instance());\n"
                        "   }\n"
                        "}\n";

                }


                source_file.close();

                //Generate Header file
                header_file.open(header);

                header_file << "#ifndef " << state_name << "_\n"
                    << "#define " << state_name << "_\n";

                if (state_parent == "Null") {
                    header_file << "#include \"../HSMState/HSMState.h\"\n";
                    header_file << "class " << state_name << " : public HSMState {\n";
                }
                else {
                    header_file << "#include \"../" << state_parent << "/" << state_parent << ".h\"\n"
                    "\n"
                    "class " << state_name << " : public " << state_parent << " {\n";
                }
                header_file << "public:\n"
                    "    static HSMState* _self;\n"
                    "    " << state_name << "();\n"
                    "    virtual void Entry();\n"
                    "    virtual void Exit();\n"
                    "    static HSMState* Instance() {\n"
                    "       return _self;\n"
                    "    }\n";

                for (int i = 0; i < state_transitions.size(); ++i) { //Parse transition conditions
                    header_file << "    virtual void " << state_transitions[i].trigger << "();\n";
                }

                if (junction.trigger != "") {
                    header_file << "    virtual void " << junction.trigger << "();\n";
                }

                header_file << "};\n";


                header_file << "#endif ";

                header_file.close();
            }
        }
    }
}

string handleGuard(string guard) {

    //Really bad hack
    //bad programmer
    return "this->_context->" + guard;
}

string handleEntryFunctions(string ef) {

    size_t found = ef.find("BSP");
    if (found == string::npos)
        ef = "this->_context->" + ef;


    return ef;
}
