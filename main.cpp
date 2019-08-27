#include <iostream>
#include <string>
#include <fcntl.h>  // use fcntl, because C++17 filesystem API sucks.
#include <dirent.h> // same reason as above comment.
#include <stdlib.h>
#include <unistd.h>
#include <ftw.h>
#include <vector>
#include <map>
#include "regex.h"
#include "lcd_display.h"
#include <arpa/inet.h>
#include <algorithm>
#include "globals.h"
#include "Tests/ProductTestRoutines/supported_products.h"

using namespace std;





AppData app_data = { }; 
SupportedProduct currentProduct;





/* initialize displays so they are available in app_data.displays[idx] */
void initialize_displays()
{
    LCDDisplay::DisableAllFramebufferConsoles();
    
    int i = 0;
    for(auto &productDisplay : currentProduct.getFramebufferNodePaths()) {
            
        app_data.displays.push_back( new LCDDisplay("lcd_display_" + to_string(i), productDisplay) );
            
        ++i;
    }
    
    //LCDDisplay lcd2("lcd_display_right", "/dev/fb1"); TODO: create /dev/fb1 for Edge!
}




/* scan for PNG image assets */
void scan_image_assets()
{
    cout << "Attempting to scan image assets..." << endl;
    
    /* ## returns >0 on file match, 0 if no match ## */
    auto filter_lambda = [] (const struct dirent* e) -> int {
        string file_name = string(e->d_name);
        
        bool condition_match_file_ext = 
            regexFindInString(file_name, R"((?:.*)(?:.){1}(?:png){1})");
        
        bool condition_is_regular_file = (e->d_type == DT_REG ? true : false);
        
        if (condition_is_regular_file && condition_match_file_ext)
            return 1;
        
        return 0;
    };
    /* ############################################# */
    
    // iterate over each entry (name) in directory, and filter
    struct dirent** entries_list;
    int n_of_entries = scandir( "Assets/Images", 
                              &entries_list, 
                              filter_lambda, 
                              alphasort );
    if (n_of_entries < 0) {
        cout << "Failed to open and scan directory for image assets!" << endl;
        exit(EXIT_FAILURE);
    }
    else if (n_of_entries == 0)
    {
        cout << "Could not find image assets in Assets/Images!" << endl;
        exit(EXIT_FAILURE);
    }
    
    // add to app_data's vector of image files to process
    while (n_of_entries--)
    {
        string file_name = string( entries_list[n_of_entries]->d_name );
        cout << "found: " << "Assets/Images/" + file_name << endl;
        // add [key]->value pair to list
        app_data.image_files.emplace( file_name, "Assets/Images/" + file_name );
        free(entries_list[n_of_entries]);
    }
    free(entries_list);
    
    cout << "Image assets scanned successfully." << endl;
}




/* check that assets and other resources this executable requires to run are present */
void check_for_assets()
{  
    string folders_to_check_for[] = {"Assets", "Assets/Images"};
    
    for (unsigned int folder_idx = 0; folder_idx < 2; ++folder_idx)
    {   
        // check that this folder exists
        {
            int tmp = open(folders_to_check_for[folder_idx].c_str(), O_RDONLY, NULL);
            if (tmp < 0)
            {
                cout << "Failed to find directory: " << folders_to_check_for[folder_idx] << endl;
                exit(EXIT_FAILURE);
            }
            if (close(tmp) < 0)
            {
                cout << "Failed to find directory (closing): " << folders_to_check_for[folder_idx] << endl;
                exit(EXIT_FAILURE);
            }
        }    
    }
    
    scan_image_assets();
}


void print_help()
{
        cout << endl << "usage: lcdtest [case insensitive: product name]" << endl << endl;
                
        cout << "Currently supported products: " << endl;
        for(auto &supportedProduct : supportedProducts)
        {
            cout << "* " << supportedProduct.getName() << endl;
        }
        
        cout << endl << endl;
}


/*  */ 
void parse_args(int argc, char* argv[]) {
    cout << "Parsing arguments..." << endl;
    
    // check # args
    if ( argc != 2 )
    {
        cout << "You have not provided me with the right # of arguments!" << endl;
        print_help();
        exit(EXIT_FAILURE);
    }

    
    // capture 1st argument - convert to lowercase string
    string inputStr = string(argv[1]);
    transform(inputStr.begin(), inputStr.end(), inputStr.begin(), ::tolower);
    
    
    for(auto &supportedProduct : supportedProducts)
    {
        string lowercaseProductName = supportedProduct.getName();
        transform(lowercaseProductName.begin(), lowercaseProductName.end(), lowercaseProductName.begin(), ::tolower);
        
        if ( inputStr.compare(lowercaseProductName)==0 )
        {
            currentProduct = supportedProduct;
            cout << "running in " << currentProduct.getName() << " mode." << endl;
            return;
        }
    }
    
    
    cout << "Unrecognized product! " << inputStr << endl;
    print_help();
    exit(EXIT_FAILURE);
}




/*
    lcdslideshow <images_folder_location> <n_of_seconds_p_image>
 */
int main(int argc, char* argv[]) {
    
    parse_args(argc, argv);
    
    initialize_displays();
    
    check_for_assets();
    
    currentProduct.executeTestRoutine();
    
    
    return EXIT_SUCCESS;
}
