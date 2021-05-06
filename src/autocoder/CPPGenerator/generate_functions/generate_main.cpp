#include "generate_main.h"
#include <vector>
#include <string>
using json = nlohmann::json;
using namespace std;
using std::filesystem::current_path;

void generate_main(json j) { //Generate the .main file of the program
    ofstream main_file;
    string HSM_name("GeneratedHSM");
    vector<string> events;

    //Get events from json
    for (const auto& stateChartitem : j.items()) {
        if (stateChartitem.key() == "events") {
            for (const auto& e : stateChartitem.value()) {
                events.push_back(e);
            }
        }
    }




    HSM_name = "Output_Files/generated_code/" + HSM_name + ".cpp";
    main_file.open(HSM_name); // Open the created source file to write into

    main_file <<"#include \"HSM/HSM.h\"\n"
                "#include <iostream>\n"
                "#include <thread>\n"
                "#include <chrono>\n"
                "#include \"Event/Event.h\"\n"
                "#include <queue>\n"
                "#include <map>\n"
                "#include <fstream>\n"
                "#include <iomanip>\n"
                "#include <direct.h>\n"
                "#define GetCurrentDir _getcwd\n"
                "using namespace std;\n"
                "\n"
                "typedef void (HSM::*stateEventHandler)(void);\n"
                "typedef std::map<std::string, stateEventHandler> state_func_map_t;\n"
                "bool parseEventsFromInput(queue<Event>&, string);\n"
                "bool dispatch(state_func_map_t , Event , HSM& );\n\n"
                "int main(int argc, char** argv) {\n"
                "    queue<Event> events;\n"
                "    parseEventsFromInput(events, argv[1]);\n"
                "    state_func_map_t m;\n\n";

    //Generate function map
    for (int i = 0; i < events.size(); i++) {
        main_file <<
            "    m[\"" << events[i] << "\"] = &HSM::" << events[i] << ";\n";
    }

    main_file << "\n\n";

    main_file <<  "    cout << \"**********QSM**********\\n\"\n         << \"-----------------------\" << std::endl;\n"
              <<  "    cout << \"**INITIALIZING MEMORY**\\n\";\n"
              <<  "    static HSM hsm;\n"
              <<  "    hsm.Initialize();\n"
              <<  "    cout << \"STARTING EVENT LISTENER\\n\";\n"
              <<  "\n"
              <<  "    while (hsm.isRunning() && !events.empty()) {\n"
              <<  "        hsm.tick();\n"
              <<  "        cout << \"Tick # \" << setw(6) << hsm.getGlobalTime() << \" State: \" << setw(20) << hsm.getCurrentState() << endl;\n"
              <<  "        if (events.front().time <= hsm.getGlobalTime()) {\n"
              <<  "           dispatch(m, events.front(), hsm);\n"
              <<  "           events.pop();\n"
              <<  "           cout << \" Current state: \" << hsm._state->stateName << endl;\n"
              <<  "        }\n"
              <<  "        else if (hsm.getTimeFlag()) {// if time flag is set, the current state has set a timer. \n "
              <<  "           if (hsm.getGlobalTime() - hsm.getTimeStart()  >= hsm.getTimeLimit()) {"
              <<  "               cout << \" Timeout exception caught in state: \" << hsm._state->stateName << \" Tick # \" << setw(6) << hsm.getGlobalTime();"
              <<  "               hsm.TIMEOUT();"
              <<  "               cout << \"Current state: \" << hsm._state->stateName << endl;\n"
              <<  "            }\n"
              <<  "        }\n"
              <<  "    std::this_thread::sleep_for(std::chrono::nanoseconds(1));\n"
              <<  "    }\n"
              <<   "\n"
              <<  "    return 0;\n"
              <<  "}\n"
              <<  "\n";


    main_file << "bool dispatch(state_func_map_t m, Event e, HSM &hsm) {\n"
              <<  "   \n"
              <<  "   bool result = true;\n"
              <<  "\n"
              <<  "   state_func_map_t::iterator x = m.find(e.eventName);\n"
              <<  "\n"
              <<  "   if (x != m.end()) {\n"
              <<  "       (hsm.*(x->second))();\n"
              <<  "       cout << \"Dispatched \" << setw(20) << e.eventName << \" @ \"\n"
              <<  "           << \"Tick # \" << setw(4) << hsm.getGlobalTime();\n"
              <<  "   }"
              <<  "   else {"
              <<  "       std::cout << e.eventName << \" not handled. in state \" << hsm._state->stateName << std::endl;\n"
              <<  "       result = false;\n"
              <<  "   }\n"
              <<  "\n"
              <<  "   return result;\n"
              <<  "}\n";

    main_file << "bool parseEventsFromInput(queue<Event> &q, string s) {\n"
              <<  "   std::ifstream infile(s);\n"
              <<  "   string en;\n"
              <<  "   int et;\n"
              <<  "   Event* e;\n"
              <<  "\n"
              <<  "   if (!(infile >> en >> et)) {\n"
              <<  "       cout << \" error, could not read first line! Abort.\" << endl;\n"
              <<  "       return false;\n"
              <<  "   }\n"
              <<  "   e = new Event(en, et);\n"
              <<  "   q.push(*e);\n"
              <<  "\n"
              <<  "   while (infile >> en >> et)\n"
              <<  "   {\n"
              <<  "       // successfully extracted one line, data is in x1, ..., x4, c.\n"
              <<  "       e = new Event(en, et);\n"
              <<  "       q.push(*e);\n"
              <<  "   }\n"
              <<  "\n"
              <<  "   return true;\n"
              <<  "\n"
              <<  "}\n";

    main_file.close();
}