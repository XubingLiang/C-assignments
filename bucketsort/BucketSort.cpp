#include "BucketSort.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

int getDigit (const long number, int pos) 
{
    unsigned int result=number;
    while(pos>0){
        result /=10;
        --pos;
    }
    return result%10;
}

int getlength(unsigned int x){
    unsigned int n=x;
    unsigned int length =0;
    while ( n /= 10 )
        length++;
    return length;
}

void radixSort(std::vector<unsigned int>& numbersToSort,std::vector<unsigned int> bucket,unsigned pos){
        if(bucket.size()<=1){
             if(bucket.size()==1){
                numbersToSort.push_back(bucket[0]);
             }
             return ;  
        } 
        std::vector<std::vector<unsigned int>> tem_buckets{10};
        for(auto n : bucket){
                unsigned int length=getlength(n);
                if(pos>length){
                       numbersToSort.push_back(n);
                } else {
                         //std::cout<<"the number is "<<n << " the length is "<<length<<" length<< the pos is "<<getDigit(n,length-pos)<<"\n";
                        tem_buckets[getDigit(n,length-pos)].push_back(n);         
                }
        }
        for(auto b : tem_buckets){
                radixSort(numbersToSort,b,pos+1);
        }
}

void BucketSort::sort(unsigned int numCores) {
        std::vector<std::thread> thread_vec;
        for(auto n: numbersToSort){
                unsigned int length=getlength(n);
                //std::cout<<"the number is "<<n << " the length is "<<length<<" length<< the pos is "<<getDigit(n,length)<<"\n";
                buckets[getDigit(n,length)-1].push_back(n);
        }
        unsigned int i=0;
        std::mutex iMutex;

        auto multi_sort = [&](std::vector<std::vector<unsigned int>> buckets){
             int index;
             while(true){
                 {
                     std::lock_guard<std::mutex> guard(iMutex);
                     if(i==buckets.size()) return;
                     index=i;
                     ++i;
                 }
                 //std::thread::id threadid = std::this_thread::get_id();
                 //std::cout<<threadid << " thread is running\n";
                 radixSort(result_buckets[index],buckets[index],1);
             }
         };

         for(unsigned int i =0; i< numCores; ++i){
             thread_vec.push_back(std::thread(multi_sort, buckets));
         }

         for(auto& t : thread_vec){
             t.join();
         }
         numbersToSort.clear();

         for(auto b : result_buckets){
             for(auto number : b){
                 numbersToSort.push_back(number);
             }
         }
}
