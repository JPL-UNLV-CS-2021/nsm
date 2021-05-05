#include "generate_HSMState.h"
#include <vector>

using std::filesystem::current_path;
using json = nlohmann::json;

void generate_eventJSON(json j) {

    json outputJson = {};

    string temp;
    vector<string> actionSet;
    for (const auto& stateChartitem : j.items()) {
        if (stateChartitem.key() == "events") {
            for (const auto& e : stateChartitem.value()) {
                outputJson.push_back(e);
            }
        }
    }

    //ACTIONSET NOW HOLDS LIST OF ALL ACTIONS
    //setting up file structor
    std::filesystem::create_directory("Output_Files/generated_code/outputJson");
    ofstream event_file;
    event_file.open("Output_Files/generated_code/outputJson/events.json");
    event_file << outputJson.dump();
    event_file.close();
}