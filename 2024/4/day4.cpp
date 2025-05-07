#include <iostream>
#include <fstream>

std::ifstream open_input_file(int file_to_run) {
    std::ifstream infile;  

    if (file_to_run == 1) {
        infile.open("test.txt");             
    } else {
        infile.open("data.txt");
    } 
    
    if (!infile) {
        std::cerr << "Could not open file\n";
        std::exit(1);
    }

    return infile;
}

int main() {
    std::cout << "Run test file (1) or actual dataset? (2)?: ";
    int file_to_run; 
    std::cin >> file_to_run;
    auto infile = open_input_file(file_to_run);


    return 0;
}