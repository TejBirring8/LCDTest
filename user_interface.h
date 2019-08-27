#include <string>
#include <vector>

#pragma once

namespace UserInterface {
    /* ask the user a multichoice question, return answer as string */
    std::string ask_multichoice_question(const std::string& question, std::vector<std::string>& possible_answers);
    
}
