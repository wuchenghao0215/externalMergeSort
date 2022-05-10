//
// Created by 吴诚颢 on 2022/5/6.
//

#include "fin.h"
#include <iostream>
#include <sstream>
#include <vector>

fin::fin(std::ifstream &input_file, int rows) : input_file(input_file), rows(rows) {}

std::vector<sharesInfo> fin::read_info() {
    std::vector<sharesInfo> shares_info;
    int i = 0;
    std::string line;
    std::string s[11];
    // read (rows) pieces of data at one time
    while (i < rows && getline(input_file, line)) {
        std::istringstream sin(line);
        for (int j = 0; j < 10; ++j) {
            getline(sin, s[j], ',');
        }
        getline(sin, s[10], '\r');
        shares_info.emplace_back(s);
        ++i;
    }
    return shares_info;
}