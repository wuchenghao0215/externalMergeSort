//
// Created by 吴诚颢 on 2022/5/9.
//

#ifndef EXTERNALMERGESORT_LOSERTREE_H
#define EXTERNALMERGESORT_LOSERTREE_H


#include "sharesInfo.h"
#include <vector>

class loserTree {
public:
    explicit loserTree(const std::vector<sharesInfo> &info_array);

    // get the minimum
    int get_top();

    // adjust the tree when modify the list given an index and new info
    void adjust(const sharesInfo &new_info);

private:
    std::vector<sharesInfo> info_array;
    int size;
    std::vector<int> loser_array;
    std::vector<int> winner_array;

    // modify nodes on the path from index to root
    void modify(int index);
};


#endif //EXTERNALMERGESORT_LOSERTREE_H
