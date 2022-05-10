//
// Created by 吴诚颢 on 2022/5/6.
//

#include "fout.h"
#include <iostream>
#include <fstream>
#include <vector>

fout::fout(std::vector<sharesInfo> &shares_info, std::ofstream &output_file) :
        shares_info(shares_info), output_file(output_file) {}

fout::fout(sharesInfo &shares_info, std::ofstream &output_file) :
        shares_info(std::vector<sharesInfo>{shares_info}), output_file(output_file) {}

void fout::write_info() {
    for (auto &i: shares_info) {
        output_file << i.get_ts_code() << ',' << i.get_trade_date() << ',';
        for (int j = 0; j < 8; ++j) {
            output_file << i.get_number()[j] << ',';
        }
        output_file << i.get_number()[8] << std::endl;
    }
}