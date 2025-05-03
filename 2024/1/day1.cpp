#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

int main() {
    std::ifstream infile("data.txt");
    if (!infile.is_open()) {
        std::cerr << "Error: could not open data.txt \n";
        return 1;
    }

    std::vector<int> col1;
    std::vector<int> col2;

    int a, b;
    while (infile >> a >> b) {
        col1.push_back(a);
        col2.push_back(b);
    }

    sort(col1.begin(), col1.end());
    sort(col2.begin(), col2.end());

    int diff = 0;
    int size = std::min(col1.size(), col2.size());
    for (int i = 0; i < size; ++i) {
        int a = col1[i];
        int b = col2[i];
        diff += std::abs(a - b);
    }

    std::cout << "Part 1: " << diff << '\n';

    int score = 0;
    for (int i : col1) {
        int num_of_repeats = 0;
        for (int j : col2) {
            if (i == j) {
                num_of_repeats++;
            }
        }
        score += i * num_of_repeats;
    }

    std::cout << "Part 2: " << score << '\n';




    // get i from col1
    // see how many times i is in col2
    // multiple i by num of apperances in col2
    // add that num to running score

/*
    for (int x : col1) {
        std::cout << "Col1: " << x << '\n';
    }

    for (int x : col2) {
        std::cout << "Col2: " << x << '\n';
    }
*/
    return 0;
}