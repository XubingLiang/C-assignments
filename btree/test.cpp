#include <algorithm>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <utility>

#include "btree.h"

using std::copy;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::set;
using std::string;
using std::vector;


const long kMinInteger = 1000000;
const long kMaxInteger = 100000000;

/**
 * Initialises random number generator.
 * The default argument uses a 'random' seed, but a specific
 * seed can be supplied to reproduce the random sequence for testing.
 **/
void initRandom(unsigned long seed = 0) {
  if (seed == 0) {
    srandom(time(NULL));
  } else {
    srandom(seed);
  }
}


/**
 * Produces a random number in the given range.
 * The random() function provides better quality random numbers
 * than the older rand() function.
 **/
long getRandom(long low, long high) {
  return (low + (random() % ((high - low) + 1)));
}


/**
 * Tries to insert numbers into the specified test container, and every time
 * the insertion succeeds (because the number wasn't previously in the btree),
 * the same number is inserted into the off-the-shelf set
 * class instance so we can later track the correctness of our btree.
 **/
size_t insertRandomNumbers(btree<long>& testContainer, vector<long>& stableContainer, size_t size) {
  size_t c = 0;
  cout << "Let's insert up to " << size << " numbers." << endl;
  for (size_t i = 0; i < size; i++) {
    long rndNum = getRandom(kMinInteger, kMaxInteger);
    auto res = testContainer.insert(rndNum);
    if (res.second) ++c;
    if(*res.first != rndNum) cout << "Wrong insert iterator!" << endl;
    stableContainer.push_back(rndNum);
    if ((i + 1) % 100000 == 0)
      cout << "Inserted some " << (i + 1) << " numbers thus far." << endl;
  }
  cout << endl;
  return c;
}

void test_reverse() {
  // insert lots of random numbers and compare with a known correct container
  btree<long> testContainer(99);
  vector<long> stableContainer1;
  vector<long> stableContainer;

  auto c = insertRandomNumbers(testContainer, stableContainer1, 1000000);

  std::sort(stableContainer1.begin(), stableContainer1.end());
  std::unique_copy(stableContainer1.begin(), stableContainer1.end(),
    std::back_inserter(stableContainer));
  cout << "size of sc is: " << stableContainer.size() << " tree is: " << c << endl;
  auto itS = stableContainer.rbegin();
  for (btree<long>::const_reverse_iterator it = testContainer.rbegin();
      it != testContainer.rend(); ++it) {
        if (*itS != *it) {cout << "NOT MATCHING.\n";}
        ++itS;
      }
  cout << "FINISH checking reverse\n";

  itS = stableContainer.rbegin();
  for (btree<long>::reverse_iterator it = testContainer.rbegin();
      it != testContainer.rend(); ++it) {
        if (*itS != *it) {cout << "NOT MATCHING.\n";}
        ++itS;
      }
  cout << "FINISH checking const_reverse\n";

  itS = stableContainer.rbegin();
//  std::cout<< testContainer<<"\n";
  for (btree<long>::iterator it = testContainer.end();
      it != testContainer.begin();++itS) {
        --it;
        if (*itS != *it) {cout << "NOT MATCHING.\n";}
      }
  cout << "FINISH checking --\n";
}

void test_modify() {
  cout << "test modify" << endl;
  btree<long> testContainer(99);
  vector<long> stableContainer1;
  vector<long> stableContainer;
  vector<long> stableContainer2;

  auto c = insertRandomNumbers(testContainer, stableContainer1, 1000000);

  std::sort(stableContainer1.begin(), stableContainer1.end());
  std::unique_copy(stableContainer1.begin(), stableContainer1.end(),
    std::back_inserter(stableContainer2));
  std::transform(stableContainer2.begin(), stableContainer2.end(), std::back_inserter(stableContainer),
    [](const auto t) {
       return t + 1;
    });
  cout << "size of sc is: " << stableContainer.size() << " tree is: " << c << endl;

  for (btree<long>::iterator it = testContainer.begin();
      it != testContainer.end(); ++it) {
        ++*it;
  }

  auto itS = stableContainer.begin();
  for (btree<long>::const_iterator it = testContainer.begin();
      it != testContainer.end(); ++it) {
        if (*itS != *it) {
          cout << "NOT MATCHING." << *itS << " from tree: " << *it << endl;
          break;
        }
        ++itS;
  }
  cout << "FINISH checking mod" << endl;
}


void print_cout() {
  btree<long> testContainer(2);
  vector<long> stableContainer;
  initRandom(100); // reinit random seed to make it stable
  insertRandomNumbers(testContainer, stableContainer, 10000);
  cout << testContainer << endl;

}

int main(void) {
  initRandom();
  test_reverse();
  test_modify();
  //print_cout();
  return 0;
}
