#include <string>
#include <algorithm>
#include <filesystem>
#include <system_error>
#include "utils.h"
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;


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
///////////////////////////////////////////////////////////

std::vector<std::string> splitCMD(std::string inp)
{
    std::stringstream ss(inp);
    std::string tok;
    std::vector<std::string> splits;
    
    while (std::getline(ss, tok, ' ')) {
        if (!tok.empty()) {
            splits.push_back(tok);
        }
    }
    
    return splits;
}

///////////////////////////////////////////////////////////////

std::string get_trimmed_cmd(std::string inp)
{
    std::vector<std::string> parts = splitCMD(inp);
    std::string concatenated_cmd = "";
    for (auto p:parts){
        concatenated_cmd = " "+concatenated_cmd;
    }
    return concatenated_cmd;
}


///////////////////////////////////////////////////////////////



std::string findExecutable(const std::string& name, const std::string& pathEnv) {
    // If name contains a slash, directly check if it's executable
    if (name.find('/') != std::string::npos) {
        fs::path execPath(name);
        if (fs::exists(execPath) && fs::is_regular_file(execPath) && 
            (fs::status(execPath).permissions() & fs::perms::owner_exec) != fs::perms::none) {
            return fs::absolute(execPath).string();
        }
        return "";
    }
    
    // Split PATH by colon
    std::stringstream ss(pathEnv);
    std::string dir;
    
    while (std::getline(ss, dir, ':')) {
        if (dir.empty()) dir = "."; // Empty component means current directory
        
        fs::path execPath = fs::path(dir) / name;
        
        try {
            // Check if file exists, is regular, and executable
            if (fs::exists(execPath) && fs::is_regular_file(execPath) && 
                (fs::status(execPath).permissions() & fs::perms::owner_exec) != fs::perms::none) {
                return fs::absolute(execPath).string();
            }
        } 
        catch (const fs::filesystem_error&) {
            // Skip inaccessible directories
            continue;
        }
    }
    
    return ""; // Not found
}