//
// Created by 吴诚颢 on 2022/5/9.
//

#ifndef EXTERNALMERGESORT_LOSERTREE_H
#define EXTERNALMERGESORT_LOSERTREE_H


#include "sharesInfo.h"
#include <vector>

class loserTree {
public:
    explicit loserTree(const std::vector<sharesInfo> &infoArray);

    // get the minimum
    int getTop();

    // adjust the tree when modify the list given an index and new info
    void adjust(const sharesInfo &newInfo);

private:
    std::vector<sharesInfo> infoArray;
    int size;
    std::vector<int> loserArray;
    std::vector<int> winnerArray;

    // modify nodes on the path from index to root
    void modify(int index);
};


#endif //EXTERNALMERGESORT_LOSERTREE_H
