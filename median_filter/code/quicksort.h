#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <iostream>
#include <string>
#include <vector>

void quicksort(std::vector<double>& data, int low_idx, int high_idx);

int quicksort_partition(std::vector<double>& data, int low_idx, int high_idx);

#endif
