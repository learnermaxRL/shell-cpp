#include <iostream>
#include <sstream>
#include <string>
#include <vector>


bool check_and_execute_command (std::string inp) {

   
    if (inp.find("echo") != std::string::npos) {
      std::cout << inp.substr(5)<<std ::endl ;
      return true ;
    }
    return false ; 
}




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


int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  while (true)
  // Uncomment this block to pass the first stage
  {  
    std::cout << "$ ";
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
