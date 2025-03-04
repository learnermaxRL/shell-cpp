#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "utils.h"


bool check_exit(std::string& inp){
  if (inp.substr(0,4) == "exit"){
    return true;
  }
  return false;
}

std::string check_invalid(std::string& input) {

    std::string err ;
    err =  input +": "+"command not found" ;
    return err;
    //
}


std::vector<std::string> commandslist = {
  "echo",
  "type",
  "exit"
};


bool check_and_execute_command (std::string inp,char* path) {

    inp = trim_whitespaces(inp);
   
    if (inp.find("type") != std::string::npos  ) {
      std::string cmd = inp.substr(inp.find("type")+5);
      
      // check if its a builtin
      if (std::find(commandslist.begin(),commandslist.end(), cmd ) != commandslist.end())
        {
          std::cout << cmd << " is a shell builtin"<<std::endl;
        }

      // check if its in path 
      else if (path != nullptr){
        std::string pth = findExecutable(cmd ,path);
        if (findExecutable(cmd ,path) != ""){
          std::cout << cmd << " is " << pth << std::endl;
        }
        else{
          std::cout << cmd << ": not found" <<std::endl;
        }
      }

      else {
          std::cout << cmd << ": not found" <<std::endl;
      }
      return true;


    }
    else if ( inp.find("echo") != std::string::npos){
        std::cout << inp.substr(5)<<std ::endl ;
      return true ;
      
    }
    else{
        return false ; 
    }

    
}






int main(int argc, char *argv[]) {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;


  char * path_var = std::getenv("PATH");

  while (true)
  // Uncomment this block to pass the first stage
  {  
    std::cout << "$ "; //aa
    std::string input;

    std::getline(std::cin, input);

    if (check_exit(input))
    {
      exit(0);
    }
    else if (check_and_execute_command(input , path_var)) {
        continue;
    }
     
    else {
      std::string err = check_invalid(input);

      if (!err.empty())
        {
          std::cout << err ;
          std::cout << std::endl;
        }
      }
    
  }
}
