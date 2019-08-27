#include "../lcd_display.h"
#include "../png_view.h"
#include "../globals.h"
#include <map>
#include <string>
#include <iostream>
#include <unistd.h>

using namespace std;

#pragma once

enum class BackgroundColour { black, white, red, green, blue };


inline void show_generic_test_pattern(LCDDisplay& lcd)
{
    
}


inline void show_defective_pixel_test(LCDDisplay& lcd, const BackgroundColour background_colour)
{
    uint8_t r = 0x00, g = 0x00, b = 0x00;
    
    switch (background_colour)
    {
        case BackgroundColour::white:
            break;
        case BackgroundColour::black:
            r = ~r;
            g = ~g;
            b = ~b;          
            break;
        case BackgroundColour::red:
            g = ~g;
            b = ~b;
            break;
        case BackgroundColour::green:
            r = ~r;
            b = ~b;
            break;
        case BackgroundColour::blue:
            r = ~r;
            g = ~g;
            break;            
    }
    
    lcd.FillScreen(r, g, b);
    lcd.UpdateScreen();
}


inline void show_uniformity_test(LCDDisplay& lcd, const unsigned int grayscale_percentage)
{
    uint8_t rgb_val = ~(0xff * grayscale_percentage);
    lcd.FillScreen(rgb_val, rgb_val, rgb_val);
    lcd.UpdateScreen();
}


// show repeating sequence of images, each image for time_period # of ms
inline void show_image_sequence(LCDDisplay& lcd, std::vector<std::string> image_filenames, const unsigned int time_period )
{
    // ensure png buffer is clear
    clear_buffer();
    
    int last_idx = 0;
    // buffer in all png files required for this sequence
    for (std::vector<std::string>::iterator it1 = image_filenames.begin();
         it1 != image_filenames.end(); ++it1) 
    {
        const std::string& image_filename = *it1;
        
        // attempt to find image in assets
        map<string, string>::iterator it = app_data.image_files.find( image_filename );
        // if not found in assets, exit!
        if (it == app_data.image_files.end())
        {
            cout << image_filename << " not found." << endl;
            exit(EXIT_FAILURE);
        }
        // buffer
        last_idx = buffer_png_image(it->second);
    }

    //cout << "size: " << image_filenames.size() << endl;
    
    // start sequence TODO: IN A NEW THREAD!
    int i = 0;
    while (1) 
    {
        view_buffered_png_image(lcd, i);
        //usleep(time_period);
        i = (i < last_idx) ? (i+1) : 0;
    }
    
    
    // ensure png buffer is clear, again
    clear_buffer();
}


inline void show_image(LCDDisplay& lcd, const std::string& image_filename )
{
    // attempt to find in assets
    map<string, string>::iterator it = app_data.image_files.find( image_filename );
    // if not found in assets, exit!
    if (it == app_data.image_files.end())
    {
        cout << image_filename << " not found." << endl;
        exit(EXIT_FAILURE);
    }
    
    view_png_image(lcd, it->second);
}


inline void show_sharpness_test(LCDDisplay& lcd, const unsigned int font_size_px)
{
    const std::string image_filename = string("sharpness_test_") + to_string(font_size_px) + string("px.png");
    
    // if found, view the images
    show_image(lcd, image_filename);
}


inline void show_viewing_angle_test(LCDDisplay& lcd)
{
    
}


inline void show_alignment_test(LCDDisplay& lcd)
{
    // @ this is tested by the test pattern function above @
}


inline void show_response_time_test(LCDDisplay& lcd)
{
    
}



