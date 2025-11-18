#include "quicksort.h"

void quicksort(std::vector<double>& data, int low_idx, int high_idx) {
    // TODO
    // Handles base case
    if (high_idx <= low_idx) {
        return;
    }

    // Partition the data within the array.
    int low_end_idx = quicksort_partition(data, low_idx, high_idx);
    // Recursively sort low partition and high partition
    quicksort(data, low_idx, low_end_idx);
    quicksort(data, low_end_idx + 1, high_idx);
}

int quicksort_partition(std::vector<double>& data, int low_idx, int high_idx) {
    // TODO
    // Pick middle element as pivot
    int midpoint = low_idx + (high_idx - low_idx) / 2;
    double pivot = data[midpoint];

    bool done = false;

    while (!done) {
        //Increment low_idx while number[low_idx] < pivot
        while (data[low_idx] < pivot) {
            low_idx += 1;
        }

        //Decrement high_idx while pivot < data[high_idx]
        while (pivot < data[high_idx]) {
            high_idx -= 1;
        }

        //If zero or one elements remain, then all numbers are partitioned. return high_idx.
        if (low_idx >= high_idx) {
            done = true;
        } else {
            //Swap data[low_idx] and data[high_idx]
            double temp = data[low_idx];
            data[low_idx] = data[high_idx];
            data[high_idx] = temp;

            //Update low_idx and high_idx
            low_idx += 1;
            high_idx -= 1;
        }
    }
    return high_idx;
}