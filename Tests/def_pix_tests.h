#include "a_test.h"
#include <vector>
#include <string>
#include "../globals.h"
#include "test_patterns.cpp"

#pragma once




ATest def_px_test_white("Defective Pixel Test - White", 
            "some test statement here.", 
            [] { 
                /* the hardware test routine here */
                show_defective_pixel_test((*app_data.displays[0]), BackgroundColour::white);
            },
            std::vector<ATestQuestion>({
                /* the questions to ask here */
                ATestQuestion("Was the screen white in colour?", std::vector<std::string> ( {"Yes", "No"} ), "No"),
                ATestQuestion("Did you see pixels of any other colour on the display?", std::vector<std::string> ( {"Yes", "No"} ), "No")
            }));


ATest def_px_test_black("Defective Pixel Test - Black", 
            "another test", 
            [] { 
                /* the hardware test routine here */
                show_defective_pixel_test((*app_data.displays[0]), BackgroundColour::black);
            },
            std::vector<ATestQuestion>({
                /* the questions to ask here */
                ATestQuestion("Was the screen black in colour?", std::vector<std::string> ( {"Yes", "No"} ), "No"),
                ATestQuestion("Did you see pixels of any other colour on the display?", std::vector<std::string> ( {"Yes", "No"} ), "No")
            }));


ATest def_px_test_red("Defective Pixel Test - Red", 
            "another test", 
            [] { 
                /* the hardware test routine here */
                show_defective_pixel_test((*app_data.displays[0]), BackgroundColour::red);
            },
            std::vector<ATestQuestion>({
                /* the questions to ask here */
                ATestQuestion("Was the screen red in colour?", std::vector<std::string> ( {"Yes", "No"} ), "No"),
                ATestQuestion("Did you see pixels of any other colour on the display?", std::vector<std::string> ( {"Yes", "No"} ), "No")
            }));


ATest def_px_test_green("Defective Pixel Test - Green", 
            "another test", 
            [] { 
                /* the hardware test routine here */
                show_defective_pixel_test((*app_data.displays[0]), BackgroundColour::green);
            },
            std::vector<ATestQuestion>({
                /* the questions to ask here */
                ATestQuestion("Was the screen green in colour?", std::vector<std::string> ( {"Yes", "No"} ), "No"),
                ATestQuestion("Did you see pixels of any other colour on the display?", std::vector<std::string> ( {"Yes", "No"} ), "No")
            }));


ATest def_px_test_blue("Defective Pixel Test - Blue", 
            "another test", 
            [] { 
                /* the hardware test routine here */
                show_defective_pixel_test((*app_data.displays[0]), BackgroundColour::blue);
            },
            std::vector<ATestQuestion>({
                /* the questions to ask here */
                ATestQuestion("Was the screen blue in colour?", std::vector<std::string> ( {"Yes", "No"} ), "No"),
                ATestQuestion("Did you see pixels of any other colour on the display?", std::vector<std::string> ( {"Yes", "No"} ), "No")
            }));
