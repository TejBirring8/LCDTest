#include <map>
#include <string>
#include <vector>
#include "lcd_display.h"

#pragma once





// data available everywhere within the application
struct AppData {
    std::map<std::string, std::string> image_files; // key (name of file) -> relative path of file (w.r.t. executable)
    std::vector<LCDDisplay*> displays;
};





// defined in main.cpp
extern AppData app_data;
