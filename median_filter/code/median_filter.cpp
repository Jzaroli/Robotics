#include "median_filter.h"
#include <iostream>
#include <queue>

median_filter::median_filter(int k) {
    this->window_size = k;
};

void median_filter::add_value(double value) {
    // Adds value to max heap if empty or value is <= to top of max heap
    if (max_heap.empty() || value <= max_heap.top()) {
        max_heap.push(value);
        ++max_heap_size;
    } else {
        // else add to min heap
        min_heap.push(value);
        ++min_heap_size;
    }

    rebalance();
};

void median_filter::remove_value(double value) {
    // marks value for delayed removal
    ++delayed_removal[value];

    // updates size counter based on related heap
    if (value <= max_heap.top()) {
        --max_heap_size;
        if (value == max_heap.top()) {
            prune_heap(max_heap);
        }
    } else {
        --min_heap_size;
        if (value == min_heap.top()) {
            prune_heap(min_heap);
        }
    }

    rebalance();
}

double median_filter::find_median() {
    double return_value;

    // return top of max heap if window size is odd
    if (window_size % 2 != 0) {
        return_value = max_heap.top();
    // else return average of two top values
    } else {
        return_value = (max_heap.top() + min_heap.top()) / 2.0;
    } 

    return return_value;
}

// double median_filter::find_average() { 
//     double sum = 0;
//     int count = 0;
    
//     std::priority_queue<double, std::vector<double>, std::greater<double>> min_heap_copy = min_heap;    
//     for (int i = 0; i < min_heap_copy.size(); i++) {
//         sum = sum + min_heap_copy.top();
//         min_heap_copy.pop();
//         count++;
//     }

//     std::priority_queue<double, std::vector<double>, std::less<double>> max_heap_copy = max_heap;
//     for (int i = 0; i < max_heap_copy.size(); i++) {
//         sum = sum + max_heap_copy.top();
//         max_heap_copy.pop();
//         count++;
//     }

//     return sum / count;
// }


void median_filter::rebalance() {
    // when max_heap has an extra element, move top to min_heap
    if (max_heap_size > min_heap_size + 1) {
        min_heap.push(max_heap.top());
        max_heap.pop();
        ++min_heap_size;
        --max_heap_size;
        prune_heap(max_heap);

    // when min_heap has more elements, move top to max_heap
    } else if (min_heap_size > max_heap_size) {
        max_heap.push(min_heap.top());
        min_heap.pop();
        ++max_heap_size;
        --min_heap_size;
        prune_heap(min_heap);
    }
}


template <typename heap_type>
void median_filter::prune_heap(heap_type& heap) {
    // removes top elements marked for removal
    while (!heap.empty() && delayed_removal[heap.top()]) {
        // Decrement the delayed count
        if (--delayed_removal[heap.top()] == 0) {
            // Remove from map if count reaches 0
            delayed_removal.erase(heap.top());
        }
        heap.pop();
    }
}