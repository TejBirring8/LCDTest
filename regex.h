#include <string>

#ifndef _REGEX_HELPERS_
#define _REGEX_HELPERS_

/* returns true if found in string (successful regex match) */
bool regexFindInString(const std::string& str, const std::string& regex);
bool regexFindInFile(const std::string& path, const std::string& regex);

#endif
