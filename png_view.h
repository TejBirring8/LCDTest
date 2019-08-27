#include "lcd_display.h"
#include <string>

#pragma once

void view_png_image(LCDDisplay& lcd, const std::string& string_filepath);
unsigned int buffer_png_image(const std::string& string_filepath);
void view_buffered_png_image(LCDDisplay& lcd, const unsigned int buffer_img);
void clear_buffer();
