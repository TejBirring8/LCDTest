#include <string>
#include <fstream>
#include <iostream>
#include <regex>
using namespace std;




/* returns true if found in string (successful regex match) */
bool regexFindInString(const string& str, const string& regex)
{
    std::regex rgx("(" + regex + ")");
    return std::regex_search(str, rgx);
}




/* returns true if found in file (successful regex match) */
bool regexFindInFile(const string& path, const string& regex)
{
    string lineBuff;
    stringstream contentBuffer;
    ifstream readOnlyStream;
    
    // open the file and buffer it's content...
    readOnlyStream.open(path);
    
    if (readOnlyStream.is_open())
    {
        // convert file content to string via the contentBuffer,
        // one line at a time.
        while (getline(readOnlyStream, lineBuff))
            contentBuffer << lineBuff << "\n";
        
        // must close file!
        readOnlyStream.close();
    }
    else
    {
        cout << "Could not open file for string search: " << path << endl;
    }

    return regexFindInString(contentBuffer.str(), regex);
}
