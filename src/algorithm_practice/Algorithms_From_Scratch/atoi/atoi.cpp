/*
  atoi() implementation

  atoi() takes a string that represents an integer value
  as an argument and returns the integer value.

*/

#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <sstream>


// Implement atoi
int my_atoi(const char *str) {
    int value;
    std::stringstream ss(str);
    ss >> value;
    if (!ss) return 0;
    return value;
}

int main(int argc, char **argv) {
    
    // test setup
    std::ifstream input_file("test.in");
    std::ofstream output_file("test.out");
    std::string str;

    // run the test
    while (std::getline(input_file, str)) {
        output_file << atoi(str.c_str()) << " -- " << my_atoi(str.c_str()) << std::endl;
    }
    
    return 0;
}
