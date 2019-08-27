#include "a_test.h"
#include <vector>
#include <string>
#include "../globals.h"
#include "test_patterns.cpp"

#pragma once




ATest visual_test_no_border("Visual Test - no border (colour) ", 
            "some test statement here.", 
            [] { 
                /* the hardware test routine here */
                show_image( (*app_data.displays[0]), "mountain_original.png" );
            },
            std::vector<ATestQuestion>({
                /* the questions to ask here */
                ATestQuestion("Was the screen white in colour?", std::vector<std::string> ( {"Yes", "No"} ), "No"),
                ATestQuestion("Did you see pixels of any other colour on the display?", std::vector<std::string> ( {"Yes", "No"} ), "No")
            }));




ATest visual_test_no_border_grayscale("Visual Test - no border (grayscale) ", 
            "some test statement here.", 
            [] { 
                /* the hardware test routine here */
                show_image( (*app_data.displays[0]), "mountain_grayscale.png" );
            },
            std::vector<ATestQuestion>({
                /* the questions to ask here */
                ATestQuestion("Was the screen white in colour?", std::vector<std::string> ( {"Yes", "No"} ), "No"),
                ATestQuestion("Did you see pixels of any other colour on the display?", std::vector<std::string> ( {"Yes", "No"} ), "No")
            }));




ATest visual_test_black_border("Visual Test - black border", 
            "some test statement here.", 
            [] { 
                /* the hardware test routine here */
                show_image( (*app_data.displays[0]), "mountain_black_border.png" );
            },
            std::vector<ATestQuestion>({
                /* the questions to ask here */
                ATestQuestion("Was the screen white in colour?", std::vector<std::string> ( {"Yes", "No"} ), "No"),
                ATestQuestion("Did you see pixels of any other colour on the display?", std::vector<std::string> ( {"Yes", "No"} ), "No")
            }));




ATest visual_test_white_border("Visual Test - white border", 
            "some test statement here.", 
            [] { 
                /* the hardware test routine here */
                show_image( (*app_data.displays[0]), "mountain_white_border.png" );
            },
            std::vector<ATestQuestion>({
                /* the questions to ask here */
                ATestQuestion("Was the screen white in colour?", std::vector<std::string> ( {"Yes", "No"} ), "No"),
                ATestQuestion("Did you see pixels of any other colour on the display?", std::vector<std::string> ( {"Yes", "No"} ), "No")
            }));




ATest visual_test_red_border("Visual Test - red border", 
            "some test statement here.", 
            [] { 
                /* the hardware test routine here */
                show_image( (*app_data.displays[0]), "mountain_red_border.png" );
            },
            std::vector<ATestQuestion>({
                /* the questions to ask here */
                ATestQuestion("Was the screen white in colour?", std::vector<std::string> ( {"Yes", "No"} ), "No"),
                ATestQuestion("Did you see pixels of any other colour on the display?", std::vector<std::string> ( {"Yes", "No"} ), "No")
            }));




ATest visual_test_green_border("Visual Test - green border", 
            "some test statement here.", 
            [] { 
                /* the hardware test routine here */
                show_image( (*app_data.displays[0]), "mountain_green_border.png" );
            },
            std::vector<ATestQuestion>({
                /* the questions to ask here */
                ATestQuestion("Was the screen white in colour?", std::vector<std::string> ( {"Yes", "No"} ), "No"),
                ATestQuestion("Did you see pixels of any other colour on the display?", std::vector<std::string> ( {"Yes", "No"} ), "No")
            }));




ATest visual_test_blue_border("Visual Test - blue border", 
            "some test statement here.", 
            [] { 
                /* the hardware test routine here */
                show_image( (*app_data.displays[0]), "mountain_blue_border.png" );
            },
            std::vector<ATestQuestion>({
                /* the questions to ask here */
                ATestQuestion("Was the screen white in colour?", std::vector<std::string> ( {"Yes", "No"} ), "No"),
                ATestQuestion("Did you see pixels of any other colour on the display?", std::vector<std::string> ( {"Yes", "No"} ), "No")
            }));
