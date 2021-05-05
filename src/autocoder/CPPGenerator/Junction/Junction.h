#include <string>

struct Junction {
    std::string trigger = "";
    std::string action = "";
    std::string guard = "";
    std::string iftarget = "";
    std::string ifaction = "";
    std::string elsetarget = "";
    std::string elseaction = "";

};