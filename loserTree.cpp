//
// Created by 吴诚颢 on 2022/5/9.
//

#include "loserTree.h"
#include <vector>

loserTree::loserTree(const std::vector<sharesInfo> &infoArray) :
        infoArray(infoArray), size(infoArray.size()),
        loserArray(std::vector<int>(size * 2)),
        winnerArray(std::vector<int>(size)) {
    // leaf node == non-leaf node + 1
    // hold array[0] to store minimum

    // initialize winnerArray
    for (int i = 0; i < size; ++i) {
        loserArray[i + size] = i;
    }

    //tournament from bottom to top
    int parent = size - 1;
    while (parent != 0) {
        modify(parent);
        --parent;
    }

    loserArray[0] = winnerArray[1];
}

// get the minimum
int loserTree::getTop() { return loserArray[0]; }

// adjust the tree when modify the list with new info
void loserTree::adjust(const sharesInfo &newInfo) {
    int index = loserArray[0];
    infoArray[index] = newInfo;
    int innerIndex = index + size;
    int parent = innerIndex / 2;
    while (parent != 0) {
        modify(parent);
        // move to its parent
        parent /= 2;
    }
    loserArray[0] = winnerArray[1];
}

// modify nodes on the path from index to root
void loserTree::modify(int index) {
    int left, right;
    if (size == index * 2 + 1) {
        left = loserArray[size];
        right = winnerArray[size - 1];
    } else if (index < size / 2) {
        left = winnerArray[index * 2];
        right = winnerArray[index * 2 + 1];
    } else {
        left = loserArray[index * 2];
        right = loserArray[index * 2 + 1];
    }
    int loser = (infoArray[left] > infoArray[right]) ? left : right;
    int winner = (loser == right) ? left : right;
    loserArray[index] = loser;
    winnerArray[index] = winner;
}