#ifndef UTILS_H
#define UTILS_H

#include <string>

std::string trim_whitespaces(const std::string& str);
std::string findExecutable(const std::string& name, const std::string& pathEnv);
std::vector<std::string> splitCMD(std::string inp);

#endif // UTILS_Haa