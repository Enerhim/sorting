#pragma once
#include <cstdint>
#include <vector>

void printList(std::vector<int64_t> &list);
uint64_t prefix_max(std::vector<int64_t> &A, uint64_t i);
uint64_t selectionSort(std::vector<int64_t> &A, uint64_t i, uint64_t &current);
