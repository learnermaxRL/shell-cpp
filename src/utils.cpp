#include <string>
#include <algorithm>
#include "util.h"

std::string trim_whitespaces(const std::string& str) {
    // Find first non-whitespace character
    auto start = str.begin();
    while (start != str.end() && std::isspace(*start)) {
        start++;
    }
    
    // Find last non-whitespace character
    auto end = str.end();
    if (start != str.end()) {
        end = str.end() - 1;
        while (end != start && std::isspace(*end)) {
            end--;
        }
        end++;
    }
    
    // Return trimmed string
    return std::string(start, end);
}