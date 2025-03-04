#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include "utils.h"

// List of built-in commands
const std::vector<std::string> BUILTIN_COMMANDS = {
    "echo",
    "type",
    "exit"
};

// Check if command is "exit"
bool isExitCommand(const std::string& input) {
    return input.substr(0, 4) == "exit";
}

// Handle "echo" command
void handleEchoCommand(const std::string& input) {
    if (input.length() <= 5) {
        // Just "echo" with no arguments or with only spaces
        std::cout << std::endl;
        return;
    }
    std::cout << input.substr(5) << std::endl;
}


// Handle "type" command
void handleTypeCommand(const std::string& input, char* pathVar) {
    std::string cmd = input.substr(input.find("type") + 5);
    cmd = trim_whitespaces(cmd);
    
    // Check if it's a builtin command
    if (std::find(BUILTIN_COMMANDS.begin(), BUILTIN_COMMANDS.end(), cmd) != BUILTIN_COMMANDS.end()) {
        std::cout << cmd << " is a shell builtin" << std::endl;
        return;
    }
    
    // Check if it's in PATH
    if (pathVar != nullptr) {
        std::string execPath = findExecutable(cmd, pathVar);
        if (!execPath.empty()) {
            std::cout << cmd << " is " << execPath << std::endl;
            return;
        }
    }
    
    // Command not found
    std::cout << cmd << ": not found" << std::endl;
}

// Execute external command
bool executeExternalCommand(const std::vector<std::string>& args, char* pathVar) {
    if (args.empty()) {
        return false;
    }
    
    std::string execPath = findExecutable(args[0], pathVar);
    if (execPath.empty()) {
        return false;
    }
    
    std::string fullCommand = args[0];
    for (size_t i = 1; i < args.size(); i++) {
        fullCommand += " " + args[i];
    }
    system(fullCommand.c_str());
    return true;
}

// Process and execute a command
bool processCommand(const std::string& input, char* pathVar) {
    std::string trimmedInput = trim_whitespaces(input);
    
    // Handle empty input
    if (trimmedInput.empty()) {
        return true;
    }
    
    // Handle exit command
    if (isExitCommand(trimmedInput)) {
        exit(0);
    }
    
    // Handle echo command
    if (trimmedInput.find("echo") == 0) {
        handleEchoCommand(trimmedInput);
        return true;
    }
    
    // Handle type command
    if (trimmedInput.find("type") == 0) {
        handleTypeCommand(trimmedInput, pathVar);
        return true;
    }
    
    // Try to execute as external command
    std::vector<std::string> args = splitCMD(trimmedInput);
    if (executeExternalCommand(args, pathVar)) {
        return true;
    }
    
    // Command not found
    std::cout << trimmedInput << ": command not found" << std::endl;
    return true;
}

int main(int argc, char *argv[]) {
    // Flush after every std::cout / std::cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;
    
    // Get PATH environment variable
    char* pathVar = std::getenv("PATH");
    
    // Main shell loop
    while (true) {
        // Display prompt
        std::cout << "$ ";
        
        // Read input
        std::string input;
        std::getline(std::cin, input);
        
        // Process command
        processCommand(input, pathVar);
    }
    
    return 0;
}