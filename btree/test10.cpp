//
// Created by shiyun on 11/10/17.
//

#include <algorithm>
#include <ostream>
#include <iterator>
#include <string>

#include "btree.h"

// test if I can change content in iterator

int main() {
    btree<std::string> bs{3};

    bs.insert("comp3000");
    bs.insert("comp6000");
    bs.insert("comp9000");

    std::cout << "begin and end change first element" << '\n';
    auto it = bs.begin();
    *it = "asdasd";
    for(; it != bs.end(); ++it){
        std::cout << *it << '\n';
    }
    it = bs.begin();
    *it = "comp3000";
    std::cout << '\n';
    std::cout << "rbegin and rend and change the first element" << '\n';
    auto rit = bs.rbegin();
    *rit = "d";
    for(; rit != bs.rend(); ++rit){
        std::cout << *rit << '\n';
    }
    rit = bs.rbegin();
    *rit = "comp9000";
    std::cout << '\n';
    std::cout << "cbegin and cend" << '\n';
    auto cit = bs.cbegin();
    // *cit = "asdasd"; //works
    for(; cit != bs.cend(); ++cit){
        std::cout << *cit << '\n';
    }
    std::cout << '\n';
    std::cout << "crbegin and crend" << '\n';
    auto crit = bs.crbegin();
    // *crit = "asdasd"; //works
    for(; crit != bs.crend(); ++crit){
        std::cout << *crit << '\n';
    }


    return 0;
}

