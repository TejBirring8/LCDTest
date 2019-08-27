#include "a_test.h"
#include <vector>
#include <string>
#include "../globals.h"
#include "test_patterns.cpp"

#pragma once




ATest uniformity_test_25_percent("Display Uniformity Test - 25% grayscale ", 
            "some test statement here.", 
            [] { 
                /* the hardware test routine here */
                show_uniformity_test((*app_data.displays[0]), 25);
            },
            std::vector<ATestQuestion>({
                /* the questions to ask here */
                ATestQuestion("Was the screen white in colour?", std::vector<std::string> ( {"Yes", "No"} ), "No"),
                ATestQuestion("Did you see pixels of any other colour on the display?", std::vector<std::string> ( {"Yes", "No"} ), "No")
            }));




ATest uniformity_test_50_percent("Display Uniformity Test - 50% grayscale ", 
            "some test statement here.", 
            [] { 
                /* the hardware test routine here */
                show_uniformity_test((*app_data.displays[0]), 50);
            },
            std::vector<ATestQuestion>({
                /* the questions to ask here */
                ATestQuestion("Was the screen white in colour?", std::vector<std::string> ( {"Yes", "No"} ), "No"),
                ATestQuestion("Did you see pixels of any other colour on the display?", std::vector<std::string> ( {"Yes", "No"} ), "No")
            }));




ATest uniformity_test_75_percent("Display Uniformity Test - 75% grayscale ", 
            "some test statement here.", 
            [] { 
                /* the hardware test routine here */
                show_uniformity_test((*app_data.displays[0]), 75);
            },
            std::vector<ATestQuestion>({
                /* the questions to ask here */
                ATestQuestion("Was the screen white in colour?", std::vector<std::string> ( {"Yes", "No"} ), "No"),
                ATestQuestion("Did you see pixels of any other colour on the display?", std::vector<std::string> ( {"Yes", "No"} ), "No")
            }));
