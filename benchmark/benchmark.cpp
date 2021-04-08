//
// Created by Mengwen Li (ml4643) on 4/8/2021.
//

#include <chrono>
#include <iostream>

#include "bench.h"
#include "projectdb/projectdb.h"

using namespace std;
using namespace projectdb;

using kvp_vec = vector<pair<string, string>>;

const int data_size = 5000;
const int word_len = 100;

int main() {
    cout << "Starting..." << endl;
    struct bench_stats bs;
    kvp_vec kvs = gen_rand(data_size, word_len);

    auto start = chrono::steady_clock::now();
    run_bench(bs, kvs);
    auto stop = chrono::steady_clock::now();
    cout << chrono::duration<double>(stop - start).count() << "\n";
    cout << "Randomly generated:\n";
    print_stats(bs);

    //	kvs = read_csv("../benchmarks/USvideos.csv",data_size);
    //	if(data_size != kvs.size()) {
    //	    cerr << "Error parsing file..." << endl;
    //	    return -1;
    //	}
    //	run_bench(bs,kvs);
    //	print_stats(bs);
}
