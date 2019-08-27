#include "a_test.h"
#include <vector>
#include <string>
#include "../globals.h"
#include "test_patterns.cpp"

#pragma once




ATest response_time_test("Defective Pixel Test - White", 
            "some test statement here.", 
            [] { 
                /* the hardware test routine here */
                
                show_image_sequence((*app_data.displays[0]), 
                                    std::vector<std::string>({
                                        "response_time_test_1.png",
                                        "response_time_test_2.png",
                                    }), 
                                    60); 
            },
            std::vector<ATestQuestion>({
                /* the questions to ask here */
                ATestQuestion("Was the screen white in colour?", std::vector<std::string> ( {"Yes", "No"} ), "No"),
                ATestQuestion("Did you see pixels of any other colour on the display?", std::vector<std::string> ( {"Yes", "No"} ), "No")
            }));
