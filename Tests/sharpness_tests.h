#include "a_test.h"
#include <vector>
#include <string>
#include "../globals.h"
#include "test_patterns.cpp"

#pragma once




ATest sharpness_test_10px_font(
            "Display Sharpness Test - 10px font ", 
            "some test statement here.", 
            [] { 
                /* the hardware test routine here */
                show_sharpness_test((*app_data.displays[0]), 10);
            },
            std::vector<ATestQuestion>({
                /* the questions to ask here */
                ATestQuestion("Was the screen white in colour?", std::vector<std::string> ( {"Yes", "No"} ), "No"),
                ATestQuestion("Did you see pixels of any other colour on the display?", std::vector<std::string> ( {"Yes", "No"} ), "No")
            }));


ATest sharpness_test_12px_font(
            "Display Sharpness Test - 10px font ", 
            "some test statement here.", 
            [] { 
                /* the hardware test routine here */
                show_sharpness_test((*app_data.displays[0]), 12);
            },
            std::vector<ATestQuestion>({
                /* the questions to ask here */
                ATestQuestion("Was the screen white in colour?", std::vector<std::string> ( {"Yes", "No"} ), "No"),
                ATestQuestion("Did you see pixels of any other colour on the display?", std::vector<std::string> ( {"Yes", "No"} ), "No")
            }));


ATest sharpness_test_14px_font(
            "Display Sharpness Test - 10px font ", 
            "some test statement here.", 
            [] { 
                /* the hardware test routine here */
                show_sharpness_test((*app_data.displays[0]), 14);
            },
            std::vector<ATestQuestion>({
                /* the questions to ask here */
                ATestQuestion("Was the screen white in colour?", std::vector<std::string> ( {"Yes", "No"} ), "No"),
                ATestQuestion("Did you see pixels of any other colour on the display?", std::vector<std::string> ( {"Yes", "No"} ), "No")
            }));


ATest sharpness_test_16px_font(
            "Display Sharpness Test - 10px font ", 
            "some test statement here.", 
            [] { 
                /* the hardware test routine here */
                show_sharpness_test((*app_data.displays[0]), 16);
            },
            std::vector<ATestQuestion>({
                /* the questions to ask here */
                ATestQuestion("Was the screen white in colour?", std::vector<std::string> ( {"Yes", "No"} ), "No"),
                ATestQuestion("Did you see pixels of any other colour on the display?", std::vector<std::string> ( {"Yes", "No"} ), "No")
            }));


