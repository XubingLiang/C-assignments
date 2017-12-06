#ifndef BUCKET_SORT_H
#define BUCKET_SORT_H

#include <vector>

struct BucketSort {
	
	// vector of numbers
	std::vector<unsigned> numbersToSort;
	std::vector<std::vector<unsigned int>> buckets{
		std::vector<unsigned int>(),
		std::vector<unsigned int>(),
		std::vector<unsigned int>(),
		std::vector<unsigned int>(),
		std::vector<unsigned int>(),
		std::vector<unsigned int>(),
		std::vector<unsigned int>(),
		std::vector<unsigned int>(),
		std::vector<unsigned int>(),
		std::vector<unsigned int>(),
	};
	std::vector<std::vector<unsigned int>> result_buckets{
		std::vector<unsigned int>(),
		std::vector<unsigned int>(),
		std::vector<unsigned int>(),
		std::vector<unsigned int>(),
		std::vector<unsigned int>(),
		std::vector<unsigned int>(),
		std::vector<unsigned int>(),
		std::vector<unsigned int>(),
		std::vector<unsigned int>(),
		std::vector<unsigned int>(),
	};
	void sort(unsigned int numCores);
};

#endif /* BUCKET_SORT_H */
