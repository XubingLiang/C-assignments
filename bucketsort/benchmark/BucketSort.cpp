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

void radixSort(std::vector<unsigned int>& result,std::vector<unsigned int> bucket,unsigned pos){
        if(bucket.size()<=1){
             if(bucket.size()==1){
                result.push_back(bucket[0]);
             }
             return;  
        } 
        std::vector<std::vector<unsigned int>> tem_buckets(10);
        for(auto n : bucket){
                unsigned int length=getlength(n);
                if(pos>length){
                       result.push_back(n);
                } else {
                        tem_buckets[getDigit(n,length-pos)].push_back(n);         
                }
        }
        bucket.clear();
        for(auto b : tem_buckets){
                if(b.size() > 0){
                    unsigned int value = b[0];
                    bool same = true;
                    for(unsigned i = 0; i< b.size(); ++i){
                        if(b[i] != value){
                            radixSort(result,b,pos+1);
                            same=false;
                            break;
                        }
                    }
                    if(same){
                        std::move(b.begin(),b.end(),std::back_inserter(result));
                    }
                    
                }
                b.clear();           
        }
        tem_buckets.clear();
        return;
}

void BucketSort::sort(unsigned int numCores) {
        std::vector<std::vector<unsigned int>> buckets(10);
        std::vector<std::vector<unsigned int>> result_buckets(10);
        std::vector<std::thread> thread_vec;
        for(auto n: numbersToSort){
                unsigned int length=getlength(n);
                // std::cout<<"the number is "<<n << " the length is "<<length<<" length<< the pos is "<<getDigit(n,length)<<"\n";
                buckets[getDigit(n,length)].push_back(n);
        }
        unsigned int i=0;
        std::mutex iMutex;
        numbersToSort.clear();

        auto multi_sort = [&](std::vector<std::vector<unsigned int>> buckets){
             while(true){
                 int index;
                 {
                     std::lock_guard<std::mutex> guard(iMutex);
                     if(i >=buckets.size()) return;
                     index=i;
                     ++i;
                 }
                 //std::thread::id threadid = std::this_thread::get_id();
                 //std::cout<<threadid << " thread is running\n";
                if(!(std::adjacent_find(buckets[index].begin(), buckets[index].end(), std::not_equal_to<unsigned>() ) == buckets[index].end())) {
                    radixSort(result_buckets[index],buckets[index],1);
                } else {
                    result_buckets[index]=buckets[index];
                }
             }
         };
         for(unsigned int i =1; i< numCores; ++i){
             thread_vec.push_back(std::thread(multi_sort, buckets));
         }
         //std::cout<<"number of cores"<<thread_vec.size()<<"\n";
         // std::thread::id threadid = std::this_thread::get_id();
         // std::cout<<threadid << "Main thread is running\n";
         multi_sort(buckets);
         for(auto& t : thread_vec){
             t.join();
         }

        
         thread_vec.clear();

         for(auto b : result_buckets){
             std::move(b.begin(),b.end(),std::back_inserter(numbersToSort));
         }
}
