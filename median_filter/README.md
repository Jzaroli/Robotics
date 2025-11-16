# Rolling Median Filter for Sensor Noise Reduction

# Objective
Sensor noise is a common occurrence and can be a hindrance to robotics perception. Improving
sensor input data quality by removing random fluctuations that degrade clarity, accuracy, and detail
thus improves quality of inference by ML models and ultimately robotics decision making. In robotics,
this helps smooth noisy distance sensors, gyroscope readings, or visual depth data.  
  
This project’s objective is to implement a real-time median filter that uses two heaps (a min-heap and
a max-heap) to efficiently maintain a rolling median over a fixed-size sliding window of sensor data.
Real-time applications require efficiency which is why this algorithm uses the heap-based approach
rather than sorting at every step.

# Background
Personal motivations for this project include an interest in robotics and a desire to move deeper into
algorithmic optimizations. Median filters are foundational in robotics, offering exposure to real-time
data handling, heap-based algorithms, and statistical estimations.  
  
On the technical front, noisy sensors are inevitable; all sensors produce noise. Traditional filters, like moving average filters, can smooth noise but distort sudden changes. Averages are sensitive to
outliers where a single very high or low reading pulls the average toward it. On the other hand,
median filtering preserves edge information and sudden jumps better. The median ignores the
magnitude of the extremes. For production applications, computing medians quickly enough for
streaming data is tricky, which is why this algorithm relies on the two-heap method to efficiently make
the calculation.

# Proposed Solution
The algorithm itself will:
* Continuously receive an input data stream.
* Maintain a sliding window of the most recent readings.
* Use two heaps: a max and a min-heap to split the data.
* Calculate the median.
This algorithm provides O(log n) time for insertion and deletion as opposed to O(n log n) time with a
straight forward sorting algorithm.  
  
A max heap is used to track the lower half of the readings, while a min-heap is used to track the
upper half of the readings. They then allow constant-time access to the median elements. And, they
efficiently rebalance when new data is added or old data is removed. If the window size is even, I will
average the two middle values to retrieve the median.

# Challenges

* One of the key challenges of this algorithm is removing the older reading from the correct
heap. This may require tracking expired values or leveraging a hash map to simplify the
process.
* Filter window sizes need to be carefully managed after each insertion/deletion and remain
closely aligned with a difference of less than or equal to 1.
* Memory leaks must be prevented and heap allocation carefully managed.
* Creating synthetic data for testing the algorithm will also be a challenge. Note: The
alternative, inefficient sorting algorithm will also need to be created for proper comparison.

# Expected Outcomes
* A working rolling median filter algorithm written in C++ that both inserts and removes sensor data values.
* The alternative, inefficient sorting algorithm; for comparison.
* Demonstrated improvements in noise reduction between the two.
* Data visualizations for the results with statistical analysis; potential hypothesis testing on
repeated trials or similar. Using: Python/Matplotlib.
* Stretch Goals:
  * Extension to different data input types.
  * Integration with an Arduino board; likely using a simple ultrasonic distance sensor. This may be constrained by the Arduino’s limited memory.

# References
* https://algo.monster/liteproblems/480
* https://thewayofnada.medium.com/a-very-thorough-solution-to-sliding-window-median-and-some-heap-magics-5091a3ed1cdc
* https://docs.wpilib.org/en/stable/docs/software/advanced-controls/filters/median-filter.html
* https://stackoverflow.com/questions/79639056/how-can-i-efficiently-maintain-median-in-a-dynamic-data-stream-with-support-for?utm_source=chatgpt.com
* https://www.edn.com/median-filters-an-efficient-way-to-remove-impulse-noise/?utm_source=chatgpt.com