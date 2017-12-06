#include <algorithm>
#include <iostream>
#include <iterator>

#include "btree.h"

void foo(const btree<int> &b) {

  std::copy(b.begin(), b.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;
}

int main(void) {
  btree<int> b;

  b.insert(1);
  b.insert(10);
  b.insert(3);
  b.insert(4);

  auto fk = b.begin();
  for(int i =0; i < 4; ++i)
      ++fk;
  std::cout<<"fdfdf "<< *fk<<"\n";
  std::cout<<"fdfdf "<< *b.end()<<"\n";
  for(btree<int>::iterator iter = b.begin(); iter != b.end(); ++iter)
    std::cout << *iter << std::endl;
  std::cout<< "BEFORE\n";
  std::cout<< *b.begin()<<"\n";
  std::cout<< "AFTER\n";
  foo(b);
  
  return 0;
}
