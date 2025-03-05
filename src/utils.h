#ifndef UTILS_H
#define UTILS_H


#include <string>
#include <vector>

std::string trim_whitespaces(const std::string& str);
std::string findExecutable(const std::string& name, const std::string& pathEnv);
std::vector<std::string> splitCMD(std::string inp);
std::string get_trimmed_cmd(std::string inp);

#endif // UTILS_Haa