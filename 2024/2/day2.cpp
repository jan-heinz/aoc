#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>


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

bool is_strictly_safe(const std::vector<int>& row) {
    bool increasing = true;
    bool decreasing = true;

    for (int j = 0; j + 1 < row.size(); ++j) {
        int difference = row.at(j + 1) - row.at(j);
        if (std::abs(difference) < 1 || std::abs(difference) > 3) {
            return false;
        }
        if (difference <= 0) increasing = false;
        if (difference >= 0) decreasing = false;
    }

    return increasing || decreasing;
}

bool is_safe_with_dampener(const std::vector<int>& row) {
    if (is_strictly_safe(row)) {
        return true;
    }

    for (int k = 0; k < row.size(); ++k) {
        std::vector<int> temp;
        temp.reserve(row.size() - 1);

        for (int i = 0; i < row.size(); ++i) {
            if (i != k) temp.push_back(row[i]);
        }
        if (is_strictly_safe(temp)) return true;
    }
    return false;
}


int main() {
    std::cout << "Run test file (1) or actual dataset? (2)?: ";
    int file_to_run; 
    std::cin >> file_to_run;
    auto infile = open_input_file(file_to_run);

    std::vector<std::vector<int>> grid;
    std::string line;
    while (std::getline(infile, line)) {
        std::vector<int> row;
        std::istringstream iss(line);
        int x;

        while (iss >> x) {
            row.push_back(x);
        }

        grid.push_back(std::move(row));
    }

    int safe_reports = 0;
    for (auto const& row : grid) {
        if (is_safe_with_dampener(row)) {
            ++safe_reports;
        }
    }
    std::cout << "num of safe reports: " << safe_reports << '\n';
/*
    for (auto i = 0; i < grid.size(); ++i) {
        for (auto j = 0; j < grid[i].size(); ++j) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << '\n';
    } */

    return 0;
}

  // two conditions for valid report
        // 1: each col is all increasing or all decreasing 
        // 1, 2, 3 = VALID
        // 1, 4, 2 = INVALID
        // 4, 2, 2 = INVALID
        // 4, 3, 2 = VALID

        // 2: each adjacent col differ by at least 1 and at most 3
        // 1, 2, 7 = INVALID (2 to 7 is increase of 5)
        // 7, 6, 2 = INVALID (6 to 2 is decrease of 4)
        // 1, 3, 6, 7, 9 = VALID (increases by 1, 2, or 3)

        // store each row of ints in its own list
        // validate with conditions above
            // if valid, increment running total
            // if not valid, go to next list