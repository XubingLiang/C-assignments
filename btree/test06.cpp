//
// Created by shiyun on 11/10/17.
//

#include <algorithm>
#include <ostream>
#include <iterator>
#include <string>

#include "btree.h"

// test find function

int main() {
    btree<int> bi{3};

    bi.insert(4000);
    bi.insert(8000);
    bi.insert(12000);
    bi.insert(1000);
    bi.insert(2000);
    bi.insert(3000);
    bi.insert(5000);
    bi.insert(6000);
    bi.insert(7000);
    bi.insert(9000);
    bi.insert(10000);
    bi.insert(11000);
    bi.insert(13000);
    bi.insert(14000);
    bi.insert(15000);

    bi.insert(300);
    bi.insert(600);
    bi.insert(900);

    bi.insert(1300);
    bi.insert(1600);
    bi.insert(1900);

    bi.insert(2300);
    bi.insert(2600);
    bi.insert(2900);

    bi.insert(3300);
    bi.insert(3600);
    bi.insert(3900);

    bi.insert(4300);
    bi.insert(4600);
    bi.insert(4900);

    bi.insert(5300);
    bi.insert(5600);
    bi.insert(5900);

    bi.insert(6300);
    bi.insert(6600);
    bi.insert(6900);

    bi.insert(7300);
    bi.insert(7600);
    bi.insert(7900);

    bi.insert(8300);
    bi.insert(8600);
    bi.insert(8900);

    bi.insert(9300);
    bi.insert(9600);
    bi.insert(9900);

    bi.insert(10300);
    bi.insert(10600);
    bi.insert(10900);

    bi.insert(11300);
    bi.insert(11600);
    bi.insert(11900);

    bi.insert(12300);
    bi.insert(12600);
    bi.insert(12900);

    bi.insert(13300);
    bi.insert(13600);
    bi.insert(13900);

    bi.insert(14300);
    bi.insert(14600);
    bi.insert(14900);

    bi.insert(15300);
    bi.insert(15600);
    bi.insert(15900);

    auto it = bi.find(14300);
    std::cout << *it << '\n';

    auto ait = bi.find(1);
    if(ait == bi.end()){
        std::cout << "didn't find\n";
    } else {
        std::cout << "found\n";
    }

    return 0;
}

