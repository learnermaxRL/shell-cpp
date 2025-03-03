#include <iostream>


std::string check_invalid(std::string& input) {

    std::string err ;
    err =  input +" "+":command not found" ;
    return err;

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

    std::string err = check_invalid(input);

    if (!err.empty())
      {
        std::cout << err ;
        std::cout << std::endl;
      }

  }
}
