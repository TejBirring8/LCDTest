#include "lcd_display.h"
#include <string>
#include <iostream>
#include <map>
#include "lodepng/lodepng.h"
using namespace std;

struct RawImageContext
{
    uint8_t* imageBuffer = 0;
    unsigned int imageHeight;
    unsigned int imageWidth;
};

// used by view_png_image:
static RawImageContext currentImageContext; 

// used by view_buffered_png_image:
static unsigned int nOfBufferedImages = 0;
static map<unsigned int, RawImageContext> bufferedImageContexts;




void view_png_image(LCDDisplay& lcd, const string& string_filepath) {
    uint8_t* ptr = nullptr;
    uint8_t r = 0, g = 0, b = 0;

    
    // load png image to buffer
    {
        unsigned int ret = lodepng_decode24_file(   &currentImageContext.imageBuffer, 
                                                    &currentImageContext.imageWidth, 
                                                    &currentImageContext.imageHeight, 
                                                    string_filepath.c_str() );
        
        if (ret != 0) {
            cout << "Failed to load PNG image: " << string_filepath << endl;
            exit(EXIT_FAILURE);
        }
    }
    cout << "Image decoded succesfully (" << string_filepath << "): height=" << currentImageContext.imageHeight << ", width=" << currentImageContext.imageWidth << "." << endl;
    // ########################
    
    
    // write the image to the display
    for (unsigned int y = 0; y < currentImageContext.imageHeight; ++y)
    {
        for (unsigned int x = 0; x < currentImageContext.imageWidth; ++x)
        {
            ptr = &currentImageContext.imageBuffer[   ( (y*currentImageContext.imageWidth)+x ) * 3   ];
            r = ~(*(ptr));
            g = ~(*(ptr+1));
            b = ~(*(ptr+2));

            lcd.WritePx(r, g, b, 
                              (currentImageContext.imageWidth-1)-x, 
                              (currentImageContext.imageHeight-1)-y);
        }
    }
    // ##############################
    
    
    // update display buffer!
    lcd.UpdateScreen();
    free(currentImageContext.imageBuffer);
    // ######################
}




unsigned int buffer_png_image(const std::string& string_filepath)
{    
    RawImageContext context = {};
        
    // load png image to buffer, size: (W*H*[R8 G8 B8])
    {
        unsigned int ret = lodepng_decode24_file(   &context.imageBuffer, 
                                                    &context.imageWidth, 
                                                    &context.imageHeight, 
                                                    string_filepath.c_str() );
        
        if (ret != 0) {
            cout << "Failed to load PNG image: " << string_filepath << endl;
            exit(EXIT_FAILURE);
        }
    }
    cout << "Image decoded succesfully (" << string_filepath << "): height=" << context.imageHeight << ", width=" << context.imageWidth << "." << endl;
    // ########################
    
    
    // put the image in the buffer
    unsigned int idx = nOfBufferedImages;
    bufferedImageContexts.emplace(idx, context); // TODO:: error checking
    nOfBufferedImages++;
    cout << "Image inserted in buffer at location: " << idx << endl;
    // ###########################
    
    return idx; // this is the index of this image, so return it's value
}




void view_buffered_png_image(LCDDisplay& lcd, const unsigned int buffer_img)
{
    uint8_t* ptr = nullptr;
    uint8_t r = 0, g = 0, b = 0;

    
    map<unsigned int, RawImageContext>::iterator it = bufferedImageContexts.find(buffer_img);
    if ( it == bufferedImageContexts.end() ) {
        cout << "failed to find image in buffer!" << endl;
        exit(EXIT_FAILURE);
    }
    
    RawImageContext& context = it->second;

    
    // write the image to the display
    for (unsigned int y = 0; y < context.imageHeight; ++y)
    {
        for (unsigned int x = 0; x < context.imageWidth; ++x)
        {
            ptr = &context.imageBuffer[   ( (y*context.imageWidth)+x ) * 3   ];
            r = ~(*(ptr));
            g = ~(*(ptr+1));
            b = ~(*(ptr+2));

            lcd.WritePx(r, g, b, 
                              (context.imageWidth-1)-x, 
                              (context.imageHeight-1)-y);
        }
    }
    // ##############################
    
    
    // update display buffer!
    lcd.UpdateScreen();
    // ######################
}




void clear_buffer()
{
    if (bufferedImageContexts.size() == 0)
        return;
    
    // for all buffered images:
    for (map<unsigned int, RawImageContext>::iterator it = bufferedImageContexts.begin();
         it != bufferedImageContexts.end(); /* NOTHING */ )
    {
        // free heap memory
        RawImageContext& context = it->second;
        free(context.imageBuffer);
        // delete the element in the map
        it = bufferedImageContexts.erase(it);
    }
    
    if (bufferedImageContexts.begin() != bufferedImageContexts.end())
    {
        cout << "failed to clear image buffer!" << endl;
        exit(EXIT_FAILURE);
    }
    
    // reset count
    nOfBufferedImages = 0;
}
