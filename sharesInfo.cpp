//
// Created by 吴诚颢 on 2022/5/6.
//

#include "sharesInfo.h"
#include <utility>

sharesInfo::sharesInfo() = default;

sharesInfo::sharesInfo(std::string *str) : ts_code(str[0]), trade_date(atoi(str[1].c_str())) {
    for (int i = 0; i < 9; ++i) {
        number[i] = atof(str[i + 2].c_str());
    }
}

sharesInfo::sharesInfo(const char *ts_code, int trade_date) : ts_code(ts_code), trade_date(trade_date) {}

std::string sharesInfo::get_ts_code() const { return ts_code; }

int sharesInfo::get_trade_date() const { return trade_date; }

double *sharesInfo::get_number() { return number; }

bool sharesInfo::operator==(const sharesInfo &other) const {
    return ts_code == other.ts_code && trade_date == other.trade_date;
}

bool sharesInfo::operator<(const sharesInfo &other) const {
    return ts_code < other.ts_code || (ts_code == other.ts_code && trade_date < other.trade_date);
}

bool sharesInfo::operator>(const sharesInfo &other) const {
    return other < *this;
}

bool sharesInfo::operator!=(const sharesInfo &other) const {
    return !(*this == other);
}