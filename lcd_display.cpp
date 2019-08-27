#include <string>
#include <iostream>
#include <dirent.h>
#include <fstream>
#include <sys/mman.h>
#include <fcntl.h>
#include "regex.h"
#include "lcd_display.h"
#include <linux/fb.h>
#include <sys/ioctl.h>

using namespace std;










void LCDDisplay::FillScreen(const uint8_t r, const uint8_t g, const uint8_t b)
{
    for (unsigned int y = 0; y < displayInfo.resolutionInfoInPixels.virtY; ++y)
    {
        for (unsigned int x = 0; x < displayInfo.resolutionInfoInPixels.virtX; ++x)
        {
            WritePx(r, g, b, x, y);
        }
    }
}







// look through all /sys/class/vtconsole/vtcon* directories to find
// all fb consoles associated with a framebuffer and shut them down!;
// see: <kernel_src_root>/Documentation/fb/fbcon.txt
void LCDDisplay::DisableAllFramebufferConsoles()
{
    const char* path_vtcon_root_dir = "/sys/class/vtconsole";
    
    // open vtcon root dir
    DIR* dir = opendir( path_vtcon_root_dir );
    if (dir == nullptr) {
        cout << "Could not open /sys/class/vtconsole directory! Skipping..." << endl;
        return;
        // can't disable framebuffer console at this point,
        // we can either close the app, or carry on to see if 
        // things still work (they should if no vtconsole exists).
    }
    
    cout << "/sys/class/vtconsole found! Shutting down all vtcon*..." << endl;
    
    // scan through every entry in vtcon root dir to see if we can find legit. vtcon* directories
    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr)
    {
        string dirName = string(entry->d_name);
        if (!regexFindInString(dirName, "vtcon"))
            continue;

        bool isFbcon = regexFindInFile("/sys/class/vtconsole/" + dirName + "/name", "frame buffer device");
        if (!isFbcon)
            continue;

        // so this is a legit. vtcon directory... so we need to disable this vtcon!
        cout << dirName << " is associated with a framebuffer device." << endl;
        ofstream writeOnlyStream;
        writeOnlyStream.open("/sys/class/vtconsole/" + dirName + "/bind", ios::trunc);
        writeOnlyStream << "0";
        writeOnlyStream.close();
    }
    
    cout << "Shutting down all vtcon* successful." << endl;
}







static void parseLCDDisplayInfo(LCDDisplayInfo& displayInfoOut, const fb_var_screeninfo& in, const fb_fix_screeninfo& in1)
{
    // get physical size of the display
    displayInfoOut.physicalSizeInMillimetres.height = in.height;
    displayInfoOut.physicalSizeInMillimetres.width = in.width;
    // get resolution info
    displayInfoOut.resolutionInfoInPixels.X = in.xres;
    displayInfoOut.resolutionInfoInPixels.Y = in.yres;
    displayInfoOut.resolutionInfoInPixels.virtX = in.xres_virtual;
    displayInfoOut.resolutionInfoInPixels.virtY = in.yres_virtual;
    displayInfoOut.resolutionInfoInPixels.offsetX = in.xoffset;
    displayInfoOut.resolutionInfoInPixels.offsetY = in.yoffset;
    // get pixel formatting info
    displayInfoOut.pixelFormatting.nBitsPerPixel = in.bits_per_pixel;
    displayInfoOut.pixelFormatting.nBytesPerPixel = displayInfoOut.pixelFormatting.nBitsPerPixel/8;
    displayInfoOut.pixelFormatting.displayType =
            in.grayscale == 0 ? LCDDisplayInfo::DisplayType::Colour :
            in.grayscale == 1 ? LCDDisplayInfo::DisplayType::Grayscale :
                                LCDDisplayInfo::DisplayType::FOURCC;

    displayInfoOut.pixelFormatting.usesNonStandardPixelFormatting = in.nonstd != 0;
    displayInfoOut.pixelFormatting.nBytesPerLine = in1.line_length;
    // get pixel formatting info - RED
    displayInfoOut.pixelFormatting.redBitfield.length = in.red.length;
    displayInfoOut.pixelFormatting.redBitfield.offsetFromRight = in.red.offset;
    displayInfoOut.pixelFormatting.redBitfield.msbIsRight = in.red.msb_right != 0;
    // get pixel formatting info - GREEN
    displayInfoOut.pixelFormatting.greenBitfield.length = in.green.length;
    displayInfoOut.pixelFormatting.greenBitfield.offsetFromRight = in.green.offset;
    displayInfoOut.pixelFormatting.greenBitfield.msbIsRight = in.green.msb_right != 0;
    // get pixel formatting info - BLUE
    displayInfoOut.pixelFormatting.blueBitfield.length = in.blue.length;
    displayInfoOut.pixelFormatting.blueBitfield.offsetFromRight = in.blue.offset;
    displayInfoOut.pixelFormatting.blueBitfield.msbIsRight = in.blue.msb_right != 0;
    // get pixel formatting info - ALPHA (transparency)
    displayInfoOut.pixelFormatting.alphaBitfield.length = in.transp.length;
    displayInfoOut.pixelFormatting.alphaBitfield.offsetFromRight = in.transp.offset;
    displayInfoOut.pixelFormatting.alphaBitfield.msbIsRight = in.transp.msb_right != 0;
}







static void printLCDDisplayInfo(const LCDDisplayInfo& displayInfoOut)
{
    cout << "Physical height (mm): " 			<< displayInfoOut.physicalSizeInMillimetres.height << endl;
    cout << "Physical width (mm): " 			<< displayInfoOut.physicalSizeInMillimetres.width << endl;
    cout << "Display resolution (px): " 		<< displayInfoOut.resolutionInfoInPixels.X << " X "
                                                << displayInfoOut.resolutionInfoInPixels.Y << endl;
    cout << "Virtual resolution (px): " 		<< displayInfoOut.resolutionInfoInPixels.virtX << " X "
                                                << displayInfoOut.resolutionInfoInPixels.virtY << endl;
    cout << "X Offset (virtual to visible): "	<< displayInfoOut.resolutionInfoInPixels.offsetX << endl;
    cout << "Y Offset (virtual to visible): "	<< displayInfoOut.resolutionInfoInPixels.offsetY << endl;
    cout << endl;
    cout << "	Pixel Formatting -> " 			<< endl;
    cout << "		Display Type: " 			<< LCDDisplayInfo::DisplayTypeToStr(displayInfoOut.pixelFormatting.displayType) << endl;
    cout << "		Bits per Pixel: " 			<< displayInfoOut.pixelFormatting.nBitsPerPixel
                                                << " (" << displayInfoOut.pixelFormatting.nBytesPerPixel << " Bytes)"
                                                << endl;
    cout << "		Bytes per Line: "			<< displayInfoOut.pixelFormatting.nBytesPerLine << endl << endl;
    cout << "		Red bitfield -> " 			<< endl;
    cout << "			offset (from right): " 	<< displayInfoOut.pixelFormatting.redBitfield.offsetFromRight << endl;
    cout << "			length: " 				<< displayInfoOut.pixelFormatting.redBitfield.length << endl;
    cout << "			msbIsRight: " 			<< displayInfoOut.pixelFormatting.redBitfield.msbIsRight << endl << endl;
    cout << "		Green bitfield -> " 		<< endl;
    cout << "			offset (from right): " 	<< displayInfoOut.pixelFormatting.greenBitfield.offsetFromRight << endl;
    cout << "			length: " 				<< displayInfoOut.pixelFormatting.greenBitfield.length << endl;
    cout << "			msbIsRight: " 			<< displayInfoOut.pixelFormatting.greenBitfield.msbIsRight << endl << endl;
    cout << "		Blue bitfield -> " 			<< endl;
    cout << "			offset (from right): " 	<< displayInfoOut.pixelFormatting.blueBitfield.offsetFromRight << endl;
    cout << "			length: " 				<< displayInfoOut.pixelFormatting.blueBitfield.length << endl;
    cout << "			msbIsRight: " 			<< displayInfoOut.pixelFormatting.blueBitfield.msbIsRight << endl << endl;
    cout << "		Alpha bitfield -> " 		<< endl;
    cout << "			offset: " 				<< displayInfoOut.pixelFormatting.alphaBitfield.offsetFromRight << endl;
    cout << "			length: " 				<< displayInfoOut.pixelFormatting.alphaBitfield.length << endl;
    cout << "			msbIsRight: " 			<< displayInfoOut.pixelFormatting.alphaBitfield.msbIsRight << endl;
    cout << endl;
}







LCDDisplay::LCDDisplay(const std::string& deviceName, const std::string& framebufPath) : 
    DeviceName(deviceName)
{
    int res = -1;

    /* open framebuffer node for RW */
    res = open(framebufPath.c_str(), O_RDWR);
    if (res <= 0) {
        cout << "Failed to open framebuffer: " << framebufPath << endl;
        exit(EXIT_FAILURE);
    }
    
    fdNode = res;

    /* get raw info via IOCTL */
    struct fb_var_screeninfo fb_var_info{};
    struct fb_fix_screeninfo fb_fix_info{};

    res = ioctl(fdNode, FBIOGET_VSCREENINFO, &fb_var_info);
    if (res < 0)
    {
        cout << "Failed to get display information [1] from framebuffer device (" + framebufPath + ")." << endl;
        exit(EXIT_FAILURE);
    }

    res = ioctl(fdNode, FBIOGET_FSCREENINFO, &fb_fix_info);
    if (res < 0)
    {
        cout << "Failed to get display information [2] from framebuffer device (" + framebufPath + ")." << endl;
        exit(EXIT_FAILURE);
    }

    /* parse & store info */
    parseLCDDisplayInfo(displayInfo, fb_var_info, fb_fix_info);
    printLCDDisplayInfo(displayInfo);

    /* map frame buf memory (this is the front framebuffer) */
    pFrameBufFront = (uint8_t*) mmap(
                    nullptr,
                    (size_t) (displayInfo.resolutionInfoInPixels.virtY * displayInfo.pixelFormatting.nBytesPerLine),
                    (PROT_READ | PROT_WRITE), MAP_SHARED, fdNode, (off_t) 0
            );
    
    if (pFrameBufFront == MAP_FAILED || pFrameBufFront == nullptr) {
        cout << "Failed to map framebuffer for device (" + framebufPath + ")." << endl;
        exit(EXIT_FAILURE);        
    }


    /* create a back framebuffer that we draw to until we are ready to "Update()" the screen */
    pFrameBufBack = (uint8_t*) mmap(
                nullptr, (size_t) (displayInfo.resolutionInfoInPixels.virtY * displayInfo.pixelFormatting.nBytesPerLine),
                (PROT_READ | PROT_WRITE), (MAP_PRIVATE | MAP_ANONYMOUS), -1, (off_t) 0
            );
    
    if (pFrameBufBack == MAP_FAILED) {
        cout << "Failed to create back buffer for device (" + framebufPath + ")." << endl;
        exit(EXIT_FAILURE);        
    }

    //close(fdNode);
}




