#include "generate_UserObjects.h"
#include <vector>
#include <string>
using json = nlohmann::json;
using namespace std;
using std::filesystem::current_path;
string cleanBSPCPP(string s);
string cleanBSPHPP(string s);
void eraseSubStr(std::string& mainStr, const std::string& toErase);
void generate_UserObjects(json j) {
	
    //Get files from json
    vector<string> fileNames;
    vector<string> fileContents;
    string temp = "";
    for(auto it : j.items()) {
        if (it.key() == "files") {
            for (auto userFile : it.value().items()) {

                if (userFile.key() == "bsp.cpp") {
                    fileNames.push_back(userFile.key());
                    temp = cleanBSPCPP(userFile.value());
                    fileContents.push_back(temp);
                }
                else if (userFile.key() == "bsp.hpp"){
                    fileNames.push_back(userFile.key());
                    temp = cleanBSPHPP(userFile.value());
                    fileContents.push_back(temp);
                }
                else {
                    fileNames.push_back(userFile.key());
                    fileContents.push_back(userFile.value());
                }

            }
        }
    }



    ofstream outFile;
    for (int i = 0; i < fileNames.size(); i++) {
        outFile.open("Output_Files/generated_code/UserObjects/" + fileNames[i]);
        outFile << fileContents[i];
        outFile.close();
    }

}

string cleanBSPCPP(string s){

    string badstring1 = "#include \"qpcpp.hpp\"  // QP/C++ framework API\n";
    string badstring2 = "using namespace QP;\n";
    string badstring3 = "         << QP_VERSION_STR\n";
    string badstring4 = "// callback functions needed by the framework --------------------------------";
    string badstring5 = "void QF::onStartup(void) {}";
    string badstring6 = "void QP::QF::onCleanup(void) {}";
    string badstring7 = "void QP::QF_onClockTick(void) {";
    string badstring8 = "    QF::TICK_X(0U, 0); // QF clock tick processing for rate 0\n}";
    string badstring10 = "void Q_onAssert(char const * const module, int loc) {";
    string badstring11 = "    cerr << \"Assertion failed in \" <<  module << \":\" << loc << endl;";
    string badstring12 = "    exit(-1);\n}";
    eraseSubStr(s, badstring1);
    eraseSubStr(s, badstring2);
    eraseSubStr(s, badstring3);
    eraseSubStr(s, badstring4);
    eraseSubStr(s, badstring5);
    eraseSubStr(s, badstring6);
    eraseSubStr(s, badstring7);
    eraseSubStr(s, badstring8);
    eraseSubStr(s, badstring10);
    eraseSubStr(s, badstring11);
    eraseSubStr(s, badstring12);
    return s;
}
string cleanBSPHPP(string s) {


    string badstring1 = "enum BlinkySignals {";
    string badstring2 = "enum { TICKS_PER_SEC = 100 }; // numer of clock ticks in a second";
    string badstring3 = "enum BlinkySignals {";
    string badstring4 = "    TIMEOUT_SIG = QP::Q_USER_SIG, // offset the first signal";
    string badstring5 = "    MAX_SIG\n};";
    string badstring6 = "// active object(s) used in this application -------------------------------";
    string badstring7 = "$declare${AOs::AO_Blinky}";


    eraseSubStr(s, badstring1);
    eraseSubStr(s, badstring2);
    eraseSubStr(s, badstring3);
    eraseSubStr(s, badstring4);
    eraseSubStr(s, badstring5);
    eraseSubStr(s, badstring6);
    eraseSubStr(s, badstring7);
    return s;
}

/*
 * Erase First Occurrence of given  substring from main string.
 */
void eraseSubStr(std::string& mainStr, const std::string& toErase)
{
    // Search for the substring in string
    size_t pos = mainStr.find(toErase);
    if (pos != std::string::npos)
    {
        // If found then erase it from string
        mainStr.erase(pos, toErase.length());
    }
}