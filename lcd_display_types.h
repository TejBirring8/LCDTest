//
// Created by tbirring on 18/07/19.
//
#include <string>

#ifndef FBDEV_TYPES_H
#define FBDEV_TYPES_H




struct LCDDisplayInfo {
    enum class DisplayType {  Colour, Grayscale, FOURCC  };

    static std::string DisplayTypeToStr(const DisplayType& displayType)
    {
        switch (displayType)
        {
            case DisplayType::Colour:
                return "Colour";
            case DisplayType::Grayscale:
                return "Grayscale";
            case DisplayType::FOURCC:
                return "FOURCC";
        }
    }

    struct
    {
        int X, Y;                   // actual (visual) resolution
        int virtX, virtY;           // virtual resolution
        int offsetX, offsetY;       // offset from virtual to visual resolution
    } resolutionInfoInPixels;

    struct
    {
        int height, width;
    } physicalSizeInMillimetres;    // these can be used to compute DPI of display, if we ever need to:
                                    // but seem to never be set by the driver!

    struct
    {
        DisplayType displayType;
        bool usesNonStandardPixelFormatting;
        int nBitsPerPixel;
        int nBytesPerPixel;
        int nBytesPerLine; // line_length i.e. length of a line in bytes

        struct {
            int offsetFromRight;
            int length;
            bool msbIsRight;
        } redBitfield;

        struct {
            int offsetFromRight;
            int length;
            bool msbIsRight;
        } greenBitfield;

        struct {
            int offsetFromRight;
            int length;
            bool msbIsRight;
        } blueBitfield;

        struct {
            int offsetFromRight;
            int length;
            bool msbIsRight;
        } alphaBitfield;
    } pixelFormatting;
};




#endif //FBDEV_TYPES_H

