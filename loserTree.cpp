//
// Created by 吴诚颢 on 2022/5/9.
//

#include "loserTree.h"
#include <vector>

loserTree::loserTree(const std::vector<sharesInfo> &info_array) :
        info_array(info_array), size(info_array.size()),
        loser_array(std::vector<int>(size * 2)),
        winner_array(std::vector<int>(size)) {
    // leaf node == non-leaf node + 1
    // hold array[0] to store minimum

    // initialize winner_array
    for (int i = 0; i < size; ++i) {
        loser_array[i + size] = i;
    }

    //tournament from bottom to top
    int parent = size - 1;
    while (parent != 0) {
        modify(parent);
        --parent;
    }

    loser_array[0] = winner_array[1];
}

// get the minimum
int loserTree::get_top() { return loser_array[0]; }

// adjust the tree when modify the list with new info
void loserTree::adjust(const sharesInfo &new_info) {
    int index = loser_array[0];
    info_array[index] = new_info;
    int innerIndex = index + size;
    int parent = innerIndex / 2;
    while (parent != 0) {
        modify(parent);
        // move to its parent
        parent /= 2;
    }
    loser_array[0] = winner_array[1];
}

// modify nodes on the path from index to root
void loserTree::modify(int index) {
    int left, right;
    if (size == index * 2 + 1) {
        left = loser_array[size];
        right = winner_array[size - 1];
    } else if (index < size / 2) {
        left = winner_array[index * 2];
        right = winner_array[index * 2 + 1];
    } else {
        left = loser_array[index * 2];
        right = loser_array[index * 2 + 1];
    }
    int loser = (info_array[left] > info_array[right]) ? left : right;
    int winner = (loser == right) ? left : right;
    loser_array[index] = loser;
    winner_array[index] = winner;
}