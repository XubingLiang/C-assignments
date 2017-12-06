//
// Created by shiyun on 11/10/17.
//

#include <algorithm>
#include <ostream>
#include <iterator>
#include <string>

#include "btree.h"

// test insertion

int main() {
    btree<std::string> bts;
    btree<std::string> bs{3};
    btree<int> bi;

    bs.insert("comp3000");
    bs.insert("comp6000");
    bs.insert("comp9000");
    bs.insert("comp1000");
    bs.insert("comp1500");
    bs.insert("comp2500");
    bs.insert("comp3500");
    bs.insert("comp4500");
    bs.insert("comp5500");
    bs.insert("comp6500");
    bs.insert("comp7500");
    bs.insert("comp8500");
    bs.insert("comp9300");
    bs.insert("comp9600");
    bs.insert("comp9900");

    std::cout<<bs<<"\n";
    for(auto it = bs.begin(); it != bs.end(); ++it){
        std::cout << *it << '\n';
    }


    return 0;
}

