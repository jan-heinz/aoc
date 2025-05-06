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

    
    // iterate through string
    // look only for valid key
    // valid = mul(int,int)
        // mul(4,6) VALID
        // mul(1051,4) VALID
        // mul (4,6) INVALID
    // when you find a valid key, do the multiplication
    // add all valid multiplication results

    std::string file_as_string {
        std::istreambuf_iterator<char>(infile),
        std::istreambuf_iterator<char>(),
    };

    int total = 0;
    // i + 4 because we look 4 indices ahead in the if statement
    for (auto i = 0; i + 4 < file_as_string.size(); ++i) {
        if (file_as_string.compare(i, 4, "mul(") == 0) {
            //std::cout << "Found match: " << file_as_string.substr(i, 7) << '\n';
            
            // validate first num
            auto first_num_end_index = i + 4;
            while (first_num_end_index < file_as_string.size() && std::isdigit(static_cast<unsigned char>(file_as_string[first_num_end_index]))) {
                ++first_num_end_index;
            }
            std::string first_num_str = file_as_string.substr(i + 4, first_num_end_index - (i + 4));
            int first_num = std::stoi(first_num_str);
            std::cout << "first num: " << first_num << "\n";

            // validate comma
            if (file_as_string[first_num_end_index] == ',') {
                std::cout << "comma found" << "\n";

                // validate second num
                auto second_num_start_index = first_num_end_index + 1;
                auto second_num_end_index = second_num_start_index;

                while (second_num_end_index < file_as_string.size() && std::isdigit(static_cast<unsigned char>(file_as_string[second_num_end_index]))) {
                    ++second_num_end_index;
                }

                std::string second_num_str = file_as_string.substr(second_num_start_index, second_num_end_index - second_num_start_index);
                int second_num = std::stoi(second_num_str);
                std::cout << "second num: " << second_num << "\n";

                // validate end paren
                if (file_as_string[second_num_end_index] == ')') {
                    std::cout << "( found:" << "\n";
                    int two_num_multiplied = 0;
                    two_num_multiplied += first_num * second_num;
                    std::cout << two_num_multiplied << '\n';
                    total += two_num_multiplied;
                }
            }
        }

    }   
    std::cout << total << '\n';
    return 0;
}