#include "sharesInfo.h"
#include "fin.h"
#include "fout.h"
#include "loserTree.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

const sharesInfo MAX("999999.ZZ", 99999999);

int main() {
    clock_t begin, end;
    begin = clock();


    // cut the data and sort each segment individually
    int count = 0;
    {
        ifstream in_file("../2_stocks.csv", ios::in);
        // skip the first line
        string skip;
        getline(in_file, skip);
        while (!in_file.eof()) {
            // read 100 pieces of data at one time
            auto shares_info = fin(in_file, 50).read_info();
            sort(shares_info.begin(), shares_info.end());
            string trans_path = string("trans").append(to_string(count).append(".csv"));
            ofstream trans_file(string("../").append(trans_path), ios::out);
            fout(shares_info, trans_file).write_info();
            std::cout << trans_path << " has been written successfully" << std::endl;
            trans_file.close();
            ++count;
        }
        in_file.close();
    }


    // ----------------------------------------dividing line----------------------------------------


    // merge sort (using loser tree)
    {
        auto trans_file = vector<ifstream>(count);
        for (int i = 0; i < count; ++i) {
            string trans_path = string("trans").append(to_string(i).append(".csv"));
            trans_file[i].open(string("../").append(trans_path), ios::in);
        }
        string out_path = "output.csv";
        ofstream out_file("../output.csv", ios::out);
        // write the first line
        out_file << "ts_code,trade_date,open,high,low,close,pre_close,change,pct_chg,vol,amount" << endl;
        // construct a loser tree
        auto infoArray = vector<sharesInfo>(count);
        for (int i = 0; i < count; ++i) {
            infoArray[i] = fin(trans_file[i], 1).read_info()[0];
        }
        loserTree tree(infoArray);
        int index = tree.getTop();
        while (infoArray[index] != MAX) {
            fout(infoArray[index], out_file).write_info();
            auto newInfo = fin(trans_file[index], 1).read_info();
            infoArray[index] = (newInfo.empty()) ? MAX : newInfo[0];
            tree.adjust(infoArray[index]);
            index = tree.getTop();
        }
        std::cout << out_path << " has been written successfully" << std::endl;
        for (int i = 0; i < count; ++i) { trans_file[i].close(); }
        out_file.close();
    }


    // ----------------------------------------dividing line----------------------------------------


    // create an index file
    ifstream out_file("../output.csv", ios::in);
    end = clock();
    cout << "takes " << (double) (end - begin) / CLOCKS_PER_SEC << " seconds" << endl;

    return 0;
}

