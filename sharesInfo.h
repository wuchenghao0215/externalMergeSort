//
// Created by 吴诚颢 on 2022/5/6.
//

#ifndef EXTERNALMERGESORT_SHARESINFO_H
#define EXTERNALMERGESORT_SHARESINFO_H


#include <string>

class sharesInfo {
public:
    sharesInfo();

    explicit sharesInfo(std::string *str);

    sharesInfo(const char *ts_code, int trade_date);

    std::string get_ts_code() const;

    int get_trade_date() const;

    double *get_number();

    bool operator==(const sharesInfo &other) const;

    bool operator<(const sharesInfo &other) const;

    bool operator>(const sharesInfo &other) const;

    bool operator!=(const sharesInfo &other) const;

private:
    std::string ts_code;
    int trade_date{};
    double number[9]{};
};


#endif //EXTERNALMERGESORT_SHARESINFO_H
