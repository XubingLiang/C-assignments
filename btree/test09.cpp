//
// Created by shiyun on 11/10/17.
//

#include <algorithm>
#include <ostream>
#include <iterator>
#include <string>

#include "btree.h"

// different iterator

int main() {
    btree<std::string> bs{3};

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

    std::cout << "level ordering" << '\n';
    std::cout << bs << '\n';
    std::cout << '\n';
    std::cout << "begin and end" << '\n';
    for(auto it = bs.begin(); it != bs.end(); ++it){
        std::cout << *it << '\n';
    }
    std::cout << '\n';
    std::cout << "rbegin and rend" << '\n';
    for(auto it = bs.rbegin(); it != bs.rend(); ++it){
        std::cout << *it << '\n';
    }
    std::cout << '\n';
    std::cout << "cbegin and cend" << '\n';
    for(auto it = bs.cbegin(); it != bs.cend(); ++it){
        std::cout << *it << '\n';
    }
    std::cout << '\n';
    std::cout << "crbegin and crend" << '\n';
    for(auto it = bs.crbegin(); it != bs.crend(); ++it){
        std::cout << *it << '\n';
    }


    return 0;
}

