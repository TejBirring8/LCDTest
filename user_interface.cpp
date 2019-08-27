#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "user_interface.h"

using namespace std;

string UserInterface::ask_multichoice_question( const string& question, vector<string>& possible_answers )
{
    cout << question << endl << endl;
    
    int count = 1;
    
    for(vector<string>::iterator it = possible_answers.begin(); 
        it != possible_answers.end(); ++it)
    {
        string& str = *it; 
        cout << "[" << count << "] " << *it << endl << endl;
        ++count;
        
        // convert to lowercase for comparison/validation sake
        transform(str.begin(), str.end(), str.begin(), ::tolower);
    }
    
ask_again:
    cout << "Please enter your answer: " ;
    string ins = "";
    cin >> ins;
    
    cout << endl;
    
    // repeat if inappropriate answer
    bool is_valid_answer = false;
    transform(ins.begin(), ins.end(), ins.begin(), ::tolower);
    
    for(vector<string>::iterator it = possible_answers.begin(); 
        it != possible_answers.end(); ++it)
    {
        if ( ins.compare(*it) == 0 )
            is_valid_answer = true;
    }
    
    if (!is_valid_answer)
        goto ask_again;
    
    // return valid possible answer entered by user
    return ins;
}
