//
// Created by shiyun on 11/10/17.
//

#include <algorithm>
#include <ostream>
#include <iterator>
#include <string>

#include "btree.h"

// test copy, move constructors and assignment

int main() {
    btree<std::string> bs{3};

    bs.insert("comp3000");
    bs.insert("comp6000");
    bs.insert("comp9000");


    std::cout << "Printing bs before copy constructor\n";
    std::cout << bs << '\n';
    for(auto it = bs.begin(); it != bs.end(); ++it){
        std::cout << *it << '\n';
    }
    btree<std::string> bc(bs);
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
    std::cout << "Printing bc after copy constructor form bs and insert to bs\n";
    std::cout << bc << '\n';
    // auto it = bc.begin();

    for(auto it = bc.begin(); it != bc.end(); ++it){
        std::cout << *it << '\n';
    }

    std::cout << "Printing bc2 after copy assignment from bs\n";
    btree<std::string> bc2 = bs;
    std::cout << bc2 << '\n';
    for(auto it = bc2.begin(); it != bc2.end(); ++it){
        std::cout << *it << '\n';
    }

    std::cout << "move bc2 to bc, move assignment and print bc\n";
    bc = std::move(bc2);
    for(auto it = bc.begin(); it != bc.end(); ++it){
        std::cout << *it << '\n';
    }
    std::cout << "move construct bb from bc\n";
    btree<std::string> bb{std::move(bc)};
    for(auto it = bb.begin(); it != bb.end(); ++it){
        std::cout << *it << '\n';
    }

    return 0;
}

