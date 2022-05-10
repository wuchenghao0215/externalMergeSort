//
// Created by 吴诚颢 on 2022/5/6.
//

#ifndef EXTERNALMERGESORT_FIN_H
#define EXTERNALMERGESORT_FIN_H


#include "sharesInfo.h"
#include <fstream>

class fin {
public:
    explicit fin(std::ifstream &input_file, int rows);

    std::vector<sharesInfo> read_info();

private:
    std::ifstream &input_file;
    int rows;
};


#endif //EXTERNALMERGESORT_FIN_H
