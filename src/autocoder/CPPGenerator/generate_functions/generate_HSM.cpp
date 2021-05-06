#include "generate_HSM.h"
#include <vector>
#include <unordered_map>
#include "../Node/Node.h"
#include "../Variable/Variable.h"

const int MAX_CHILDREN = 10; 
const int MAX_STATES = 10; 
 

using std::filesystem::current_path;
using json = nlohmann::json;


struct less_than_key
{
    inline bool operator() (const Node* struct1, const Node* struct2)
    {
        return (struct1->level < struct2->level);
    }
};


void generate_HSM(json j) {

   

    unordered_map<string, Node*> hash;
    vector<string> transitions;
    vector<string> events;
    vector<string> startSequence;
    vector<Node*> states;
    vector<Variable> vars;
    Node* p;

    //Store all nodes in the input file in a vector for processing

    for (const auto& stateChartitem : j.items()) {


        if (stateChartitem.key() == "events") {
            for (const auto& e : stateChartitem.value()) {
                events.push_back(e);
            }
        }

        if (stateChartitem.key() == "initialPath") {
            for (const auto& ip : stateChartitem.value()) {
                startSequence.push_back(ip);
            }
        }        
        
        if (stateChartitem.key() == "variables") {
            for (const auto& v : stateChartitem.value()) {
                Variable t;
                t.name = v["name"];
                t.type = v["type"];
                t.visibility = v["visibility"];
                t.properties = v["properties"];
                vars.push_back(t);
            }
        }

        if (stateChartitem.key() == "states") {
            for (const auto& state : stateChartitem.value()) {
                string state_name;
                string state_parent;
                vector<string> entry_functions;
                vector<string> exit_functions;
                vector<Transition> state_transitions;
                Junction junction;
                int entry_functions_count;
                int exit_functions_count;
                int state_transitions_count;
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

                    entry_functions_count = entry_functions.size();

                    if (stateMember.key() == "exitFunctions") {
                        for (const auto& exitFunc : stateMember.value()) {
                            string s = exitFunc;
                            exit_functions.push_back(s);
                        }
                    }

                    exit_functions_count = exit_functions.size();

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
                    state_transitions_count = state_transitions.size();


                    if (stateMember.key() == "junction") {

                        Junction p;
                        //if (stateMember.value().contains("trigger")) {
                        //    std::cout << stateMember.value() << "\n";
                        //    p.trigger = stateMember.value()["trigger"];
                        //    p.action = stateMember.value()["action"];
                        //    p.guard = stateMember.value()["guard"];
                        //    p.iftarget = stateMember.value()["iftarget"];
                        //    p.ifaction = stateMember.value()["ifaction"];
                        //    p.elsetarget = stateMember.value()["elsetarget"];
                        //    p.elseaction = stateMember.value()["elseaction"];

                        //}

                        junction = p;
                    }
                }


                p = new Node(state_name,
                    state_parent,
                    entry_functions,
                    exit_functions,
                    state_transitions,
                    entry_functions_count,
                    exit_functions_count,
                    state_transitions_count);

                hash[state_name] = p;
                states.push_back(p);
            }
        }
    }
    

    //For every node
    // if it has a parent, 
    //      assign the parent node pointer to state_parent on current node

    for (int i = 0; i < states.size(); i++) {
        if (states[i]->state_parent != "Null") {
            for (int j = 0; j < states.size(); j++) {
                if(states[j]->state_name == states[i]->state_parent)
                    states[i]->parentPtr = states[j];
            }
        }
        else {
            states[i]->parentPtr = nullptr;
        }
    }

    //At this point all nodes should be assigned a parent pointer or nullptr
    //To determine the level of each node
    // For every node
    //  traverse the parents until you reach null
    //  the level is the number of steps it takes
    for (int i = 0; i < states.size(); i++) {

        p = states[i];

        while (p->parentPtr != nullptr) {
            states[i]->level += 1;
            p = p->parentPtr;
        }
    }

    // The final piece we need to build initalizeMemory()
    // is the varDecl
    // We will start at the first ascii Character and continue alphabetically
    char varDecl = 65;
    string temp = "";
    int doubler = 0;
    temp += varDecl;
    for (int i = 0; i < states.size(); i++) {
        states[i]->varDecl = temp;
        if (varDecl == 'Z') {
            varDecl = 'A';
            doubler += 1;
        }
        else {
            varDecl = static_cast<char>(varDecl + 1);
        }
        temp = "";
        for (int j = 0; j <= doubler; j++) {
            temp += varDecl;
        }
    }


    /* SET UP OUTPUT FILES*/
    string source;
    string header;
    filesystem::path currPath = current_path();
    string path_string = currPath.generic_string();
    string last5 = path_string.substr(path_string.length() - 5, 5);
    if (last5 == "Debug") {
        path_string = path_string.substr(0, path_string.length() - 19);
    }
    std::filesystem::create_directory("Output_Files/generated_code/HSM");
    source = "Output_Files/generated_code/HSM/HSM.cpp";
    header = "Output_Files/generated_code/HSM/HSM.h";
    ofstream source_file, header_file;

    /* GENERATING SOURCE */
    source_file.open(source);


    //HeaderFiles
    source_file << "#include \"HSM.h\"\n";
    for (int i = 0; i < states.size(); i++) {

        source_file << "#include \"../"
            << states[i]->state_name
            << "/" << states[i]->state_name << ".h\"\n";

    }

    //BEGIN HSM Constructor  --------
    source_file << 
        "HSM::HSM() {\n\n"
        //TODO ADD Internal Variable initalizations
        "}\n";
    //END HSM Constructor --------


    //BEGIN initalizeMemory Function----------------
    source_file << "void HSM::Initialize() {\n\n"
        "setRunning(true);\n"
        "setTimeFlag(false);\n\n";

    //Need to sort by level here
    std::sort(states.begin(), states.end(), less_than_key());

    //For every state we need statements in the form
    //  static <Statename> <varDecl>; (make sure to update varDecl in the node class)
    //  <varDecl>.self = &<varDecl>;
    //  <varDecl>._context = this;
    //  <varDecl>.level = <state>.level;
    //  <varDecl>._parent = &<state>->parent->varDecl
    for (int i = 0; i < states.size(); i++) {
        source_file << "    static " << states[i]->state_name
            << " " << states[i]->varDecl << ";\n\t";

        source_file << states[i]->varDecl << "._self = &"
            << states[i]->varDecl << ";\n\t";

        source_file << states[i]->varDecl << "._context = this;\n\t";

        source_file << states[i]->varDecl << ".level = " << states[i]->level << ";\n\t";

        if (states[i]->parentPtr == nullptr) {
            source_file << states[i]->varDecl << "._parent = NULL;\n\t";

        }
        else {
            source_file << states[i]->varDecl << "._parent = &" << states[i]->parentPtr->varDecl << ";\n";

        }

        source_file << states[i]->varDecl << ".stateName = \"" << states[i]->state_name << "\";\n\t";

    }

    for (int i = 0; i < startSequence.size(); i++) {
        source_file <<
            "this->_state = " + startSequence[i] + "::Instance();\n"
            "   this->_state->Entry();\n";
    }

    source_file << "}\n\n\n";
    //END initalizeMemory


    //BEGIN STATE DELEGATION METHODS
    //For each event
    for (int i = 0; i < events.size(); i++) {
        source_file <<
            "void HSM::" + events[i] + "() {\n"
            "   _state->" + events[i] + "();\n"
            "}\n\n\n";
    }
    //END STATE DELEGATION METHODS


    source_file <<
        "std::string HSM::getCurrentState() {\n"
        "   return _state->stateName;\n"
        "}\n\n";

    //BEGIN  ChangeState()
    source_file << "void HSM::ChangeState(HSMState* s) {\n\n\t"
        << "HandleEntryExit(_state, s);\n\n\t"
        << "for (int i = 0; i < numOfExitStates; i++) {\n\t\t"
        << "exitStates[i]->Exit();\n\t"
        << "}\n\n\t"
        << "_state = s;\n\t"
        << "for (int i = numOfEntryStates - 1; i >= 0; i--) {\n\t\t"
        << "entryStates[i]->Entry();\n"
        << "}\n\n}";
    //END  ChangeState()

    //BEGIN  HandleEntryExit()
    source_file << "void HSM::HandleEntryExit(HSMState * FROM, HSMState * TO) {\n\t"
        << "HSMState* fromOriginal = FROM;\n\t"
        << "HSMState* toOriginal = TO;\n\t"
        << "numOfEntryStates = 0;\n\t"
        << "numOfExitStates = 0;\n\t"
        << "while (FROM->level != TO->level) {\n\t\t"
        << "if (FROM->level > TO->level) {\n\t\t\t"
        << "exitStates[numOfExitStates] = FROM;\n\t\t\t"
        << "numOfExitStates++;\n\t\t\t"
        << "FROM = FROM->_parent;\n\t\t"
        << "}\n\t\t"
        << "else {\n\t\t\t"
        << "entryStates[numOfEntryStates] = TO;\n\t\t\t"
        << "numOfEntryStates++;\n\t\t\t"
        << "TO = TO->_parent;\n\t\t"
        << "}\n\t"
        << "}\n\n\t"
        << "while (FROM != TO) {\n\t\t"
        << "exitStates[numOfExitStates] = FROM;\n\t\t"
        << "numOfExitStates++;\n\t\t"
        << "FROM = FROM->_parent;\n\t\t"
        << "entryStates[numOfEntryStates] = TO;\n\t\t"
        << "numOfEntryStates++;\n\t\t"
        << "TO = TO->_parent; \n\t"
        << "}\n\t"
        << "commonParent = TO;\n\t"
        << "FROM = fromOriginal;\n\t"
        << "TO = toOriginal;\n"
        << "}\n\n";
    //END  HandleEntryExit()



    //SOURCE FILE COMPLETE
    source_file.close();

    //GENERATE HEADER FILE

    int max_h_level = 0;

    for (int i = 0; i < states.size(); i++) {
        if (states[i]->level > max_h_level) {
            max_h_level = states[i]->level;
        }

    }
    max_h_level++;

    header_file.open(header);

    header_file <<
        "#ifndef HSM_\n"
        "#define HSM_\n"
        "#include \"../HSMState/HSMState.h\"\n"
        "#include <iostream>\n"
        "#define H_LEVEL " << max_h_level << "\n\n"
        "class HSMState;\n\n"
        "class HSM {\n"
        "public:\n"
        "    HSM();\n"
        "    void Initialize();\n"
        "    std::string getCurrentState();\n\n";
    for (int i = 0; i < events.size(); i++) {
        header_file <<
            "   void " + events[i] + "();\n";
    }
    header_file <<
        "\n";

    for (int i = 0; i < vars.size(); i++) {

        if (vars[i].type != "QP::QTimeEvt" && vars[i].type != "QP::QActive * const" && vars[i].name != "instance") {
            header_file <<
                "   " + vars[i].type + " " + vars[i].name + ";\n";
        }
    }

    header_file <<
        "\n"
        "    //State Design\n"
        "   HSMState * _state;\n"
        "   friend class HSMState;\n"
        "   void ChangeState(HSMState*);\n"
        "   void InitialTransition(HSMState*);\n"
        "   void HandleEntryExit(HSMState*, HSMState*);\n"
        "   //CallStacks\n"
        "   //The length of these arrays is equal to\n"
        "   //the height of the heirarchial state machine\n"
        "   HSMState* entryStates[H_LEVEL];\n"
        "   HSMState* exitStates[H_LEVEL];\n"
        "   int numOfEntryStates;\n"
        "   int numOfExitStates;\n"
        "   HSMState* commonParent;\n\n"
        "\n"
        "    bool running;\n"
        "   void setRunning(bool b) { running = b; };\n"
        "   bool isRunning() { return running; }\n"
        "\n"
        "   bool timeFlag;\n"
        "   void setTimeFlag(bool tf) { timeFlag = tf; };\n"
        "   bool getTimeFlag() { return timeFlag; }\n"
        "\n"
        "   int timeStart = 0;\n"
        "   void setTimeStart(int ts) { timeStart = ts; };\n"
        "   int getTimeStart() { return timeStart; }\n"
        "\n"
        "   int clock = 2;\n"
        "   void tick() { clock++; };\n"
        "   int getGlobalTime() { return clock; };\n"
        "\n"
        "   int timeLimit = 0;\n"
        "   void setTimeLimit(int tl) { timeLimit = tl; };\n"
        "   int getTimeLimit() { return timeLimit; };\n"
        "\n"
        "   void killTimer() {\n"
        "       timeFlag = false;\n"
        "       timeStart = getGlobalTime();\n"
        "       timeLimit = 0;\n"
        "   };\n"
        "\n"
        "   void setTimer() {\n"
        "       timeFlag = true;\n"
        "       setTimeStart(getGlobalTime());\n"
        "       timeLimit = 5;\n"
        "   };\n\n "




        "};\n\n"

        "#endif";


    header_file.close();


}