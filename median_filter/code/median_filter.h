#include <queue>
#include <vector>
#include <unordered_map>

class median_filter {
    public:
        median_filter(int k);

        void add_value(double value);
        void remove_value(double value);
        double find_median();
        // double find_average();

    private:
        int window_size;
    
        std::priority_queue<double, std::vector<double>, std::less<double>> max_heap;
        std::priority_queue<double, std::vector<double>, std::greater<double>> min_heap;
        int max_heap_size = 0;
        int min_heap_size = 0;

        std::unordered_map<double, int> delayed_removal;

        void rebalance();

        template <typename heap_type>
        void prune_heap(heap_type& heap);
};