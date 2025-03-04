#include <iostream>
#include <sstream>
#include <string>
#include <vector>
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
  "type"
};


bool check_and_execute_command (std::string inp) {

    inp = trim_whitespaces(inp);
   
    if (inp.find("type") != std::string::npos  ) {
      
      if (std::find(commandslist.begin(),commandslist.end(), inp.substr(inp.find("type")+5) ) != commandslist.end())
        {
          std::cout << inp.substr(inp.find("type")+5) << " is a shell builtin"<<std::endl;
        }

      else {
          std::string cmd = inp.substr(inp.find("type")+5);
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






int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

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
    else if (check_and_execute_command(input)) {
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
