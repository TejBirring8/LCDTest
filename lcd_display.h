//
// Created by tbirring on 18/07/19.
//
#include <string>
#include <string.h>
#include "lcd_display_types.h"

#ifndef FBDEV_H
#define FBDEV_H


class LCDDisplay {
    
    
private:
    LCDDisplayInfo displayInfo = {{ 0 }};
    int fdNode = -1;
    /* used to draw pixels to either (allocated) back-buffer or (mapped) front-buffer */
    unsigned char*        pFrameBufFront = nullptr;			                    // pointer to the mapped buffer
    unsigned char*        pFrameBufBack = nullptr;				                // pointer to the (allocated) back buffer
    volatile long long writeLoc = -1;

public:
    const std::string DeviceName;

    LCDDisplay(const std::string& deviceName, const std::string& fbdev_node);

    
    inline void WritePx(const uint8_t r, const uint8_t g, const uint8_t b, const size_t x, const size_t y)
{
    if (x > displayInfo.resolutionInfoInPixels.virtX || y > displayInfo.resolutionInfoInPixels.virtY)
        return;
    
    // TODO: need to make this more efficient!
    
     uint32_t px =   /*(0x00000000) +*/ //optimization's sake
                    (r << displayInfo.pixelFormatting.redBitfield.offsetFromRight)   |
                    (g << displayInfo.pixelFormatting.greenBitfield.offsetFromRight) |
                    (b << displayInfo.pixelFormatting.blueBitfield.offsetFromRight);
    
    writeLoc = ( /*(*/x /*+ displayInfo.resolutionInfoInPixels.offsetX)*/ * displayInfo.pixelFormatting.nBytesPerPixel )
                           + (y /*+ displayInfo.resolutionInfoInPixels.offsetY)*/ * displayInfo.pixelFormatting.nBytesPerLine);

    *(uint32_t*)(pFrameBufBack + writeLoc) = px;
}


    void FillScreen(const uint8_t r, const uint8_t g, const uint8_t b);
    
    
inline void UpdateScreen()
{
    size_t size = (displayInfo.resolutionInfoInPixels.virtY * displayInfo.pixelFormatting.nBytesPerLine);
    memcpy(pFrameBufFront, pFrameBufBack, size);
}
    
    static void DisableAllFramebufferConsoles();
};


#endif //FBDEV_H

