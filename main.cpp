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

const sharesInfo MAX_INFO("999999.ZZ", 99999999);

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
            // read k pieces of data at one time
            const int k = 100;
            vector<sharesInfo> shares_info = fin(in_file, k).read_info();

            sort(shares_info.begin(), shares_info.end());

            string trans_path = string("trans").append(to_string(count).append(".csv"));
            ofstream trans_file(string("../").append(trans_path), ios::out);
            fout(shares_info, trans_file).write_info();
            cout << trans_path << " has been written successfully" << endl;
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
        auto info_array = vector<sharesInfo>(count);
        for (int i = 0; i < count; ++i) {
            info_array[i] = fin(trans_file[i], 1).read_info()[0];
        }
        loserTree tree(info_array);
        int index = tree.get_top();
        while (info_array[index] != MAX_INFO) {
            fout(info_array[index], out_file).write_info();
            vector<sharesInfo> new_info = fin(trans_file[index], 1).read_info();
            info_array[index] = (new_info.empty()) ? MAX_INFO : new_info[0];
            tree.adjust(info_array[index]);
            index = tree.get_top();
        }

        cout << out_path << " has been written successfully" << endl;
        for (int i = 0; i < count; ++i) { trans_file[i].close(); }
        out_file.close();
    }


    // ----------------------------------------dividing line----------------------------------------


    // create and write an index file
    {
        ifstream out_file("../output.csv", ios::in);
        ofstream index_file("../index.csv", ios::out);

        // skip the first line
        string skip;
        getline(out_file, skip);

        streampos cur_pos = out_file.tellg();
        sharesInfo pre_info = MAX_INFO;
        vector<sharesInfo> cur_info = fin(out_file, 1).read_info();
        while (!cur_info.empty()) {
            if (pre_info.get_ts_code() != cur_info[0].get_ts_code() ||
                pre_info.get_trade_date() / 100 != cur_info[0].get_trade_date() / 100) {
                index_file << cur_info[0].get_ts_code() << ',' << cur_info[0].get_trade_date() / 100
                           << ',' << cur_pos << endl;
                pre_info = cur_info[0];
            }
            cur_pos = out_file.tellg();
            cur_info = fin(out_file, 1).read_info();
        }

        cout << "index.csv has been written successfully" << endl;
        out_file.close();
        index_file.close();
    }


    end = clock();
    cout << "sorting and indexing takes " << (double) (end - begin) / CLOCKS_PER_SEC << " seconds" << endl;

    return 0;
}

