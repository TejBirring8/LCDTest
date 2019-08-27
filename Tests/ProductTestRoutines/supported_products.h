#include "_product_display_abstraction.h"
#include "edge_test.h"
#include "avalon_test.h"

class SupportedProduct 
{
private:
    string name; // this will be matched with command-line argument in lower-case!
    ProductFramebuffers displays;
    ProductTestRoutine testRoutine;
    
    
    
    
public:
    SupportedProduct(const std::string& productName, const ProductFramebuffers& productDisplays, const ProductTestRoutine& productTestRoutine) :
        name(productName), displays(productDisplays), testRoutine(productTestRoutine)
    {}
    
    
    SupportedProduct(){}
    
    const string& getName() { return name; }
    
    const ProductFramebuffers& getFramebufferNodePaths() { return displays; }
    
    void executeTestRoutine()
    {
        executeProductTestRoutine(testRoutine);
    }
};




vector<SupportedProduct> supportedProducts { 
    SupportedProduct( "Edge", 
                      ProductFramebuffers( {"/dev/fb0"} ),
                      edgeTestRoutine ),
                      
                        
                      
                      
    SupportedProduct( "Avalon", 
                      ProductFramebuffers( {"/dev/fb0"} ),
                      avalonTestRoutine )                                             
};
