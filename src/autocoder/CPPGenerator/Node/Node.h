#ifndef QSM_NODE_H
#define QSM_NODE_H


#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>
#include "../Junction/Junction.h"
#include "../Transition/Transition.h"
using namespace std;

class Node {

public:
    Node* parentPtr = nullptr;
    //Node* children[MAX_CHILDREN];
    int level = 0;
    string varDecl = "";

    string state_name;
    string state_parent;
    vector<string> entry_functions;
    vector<string> exit_functions;
    vector<Transition> state_transitions;
    Junction junction;
    int entry_functions_count;
    int exit_functions_count;
    int state_transitions_count;

    Node() {

    }

    Node(string sn,
        string sp,
        vector<string> entry,
        vector<string> exit,
        vector<Transition> trans,
        int enfc,
        int exfc,
        int stc) {
        state_name = sn;
        state_parent = sp;
        entry_functions = entry;
        exit_functions = exit;
        state_transitions = trans;
        entry_functions_count = enfc;
        exit_functions_count = exfc;
        state_transitions_count = stc;
    }


};

#endif //QSM_GENERATE_STATES_H
