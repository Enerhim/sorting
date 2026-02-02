#include "sort.hpp"
#include <iostream>
#include <utility>

void printList(std::vector<int64_t> &list) {
  for (uint64_t i = 0; i < list.size(); i++) {
    std::cout << list[i] << ", ";
  }
  std::cout << std::endl;
}

uint64_t prefix_max(std::vector<int64_t> &A, uint64_t i) {
  // Return the index of the maximum in A[:i+1]
  if (i > 0) {
    uint64_t j = prefix_max(A, i - 1);
    if (A[i] < A[j])
      return j;
  }
  return i;
}

uint64_t selectionSort(std::vector<int64_t> &A, uint64_t i, uint64_t &current) {
  if (i > 0) {
    uint64_t max_index = prefix_max(A, i);
    current = max_index;
    std::swap(A[max_index], A[i]);
  }

  return i - 1;
}
