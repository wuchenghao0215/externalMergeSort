//
// Created by 吴诚颢 on 2022/5/6.
//

#ifndef EXTERNALMERGESORT_FOUT_H
#define EXTERNALMERGESORT_FOUT_H


#include "sharesInfo.h"
#include <vector>

class fout {
public:
    fout(std::vector<sharesInfo> &shares_info, std::ofstream &output_file);

    fout(sharesInfo &shares_info, std::ofstream &output_file);

    void write_info();

private:
    std::vector<sharesInfo> shares_info;
    std::ofstream &output_file;
};


#endif //EXTERNALMERGESORT_FOUT_H
