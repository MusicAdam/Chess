#include "Debug.h"

//Make this class dynamic , aka, user defined logs msgs can be put into any log, and then output with a nice menu that can be brought up with the d key

Debug::Debug()
{
    //ctor
}

void Debug::msg(const std::string& msg){
    std::cout << msg << std::endl;
}
