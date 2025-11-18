#include <iostream>
#include <random>
#include "../code/median_filter.cpp"

using namespace std;

int main(){

    // welcome statement
    cout << endl;
    cout << "**** Sensor Noise Reduction using a Median Filter ****" << endl; 
    cout << "**** Demo Application ****" << endl;
    cout << endl;

    bool is_menu_active = true; // value for menu while loop 

    while (is_menu_active) {
        cout << "MENU:" << endl;
        cout << endl;
        cout << "1) Test Sensor Noise Reduction with a Naive Sorting Algorithm." << endl;
        cout << "2) Test Sensor Noise Reduction with a Median Filter." << endl;
        
        string chosen_option = "";
        cout << endl << "Enter menu selection (Q to quit): " << endl;
        cin >> chosen_option;

        if (chosen_option == "Q")
        {
            is_menu_active = false;
            cout << "Quitting the application..." << endl;
        } else if (chosen_option == "1") {
            cout << endl;

        } else if (chosen_option == "2") {
            cout << endl;

            bool is_option_active = true; // value for option while loop 

            while (is_option_active) {
                int window_option = 0;
                cout << "This program will randomly generate 30 gamm distributed numbers with shape of 2 and a scale of 2, then slide a median filter window across the numbers to return the median at each step." << endl;
                cout << endl << "What size sliding window do you want to use (pick an integer between 2 and 10)?" << endl;
                cin >> window_option;

                if (window_option >= 2 && window_option <= 10) {
                    // initializes median filter with window size option
                    median_filter filter(window_option);

                    // boiler plate for gamma distributed number generation
                    random_device rd;
                    mt19937 gen(rd());
                    double shape = 2.0;
                    double scale = 2.0;
                    std::gamma_distribution<double> gamma_dist(shape, scale);

                    // generates 20 doubles and stores them in a vector
                    vector<double> numbers;
                    for (int i = 0; i < 30; ++i) {
                        double val = gamma_dist(gen);
                        numbers.push_back(val);
                    }

                    // stores the median of the first window 
                    for (int i = 0; i < window_option; ++i) {
                        filter.add_value(numbers[i]);
                    }
                    
                    vector<double> results = {filter.find_median()};
                    cout << endl;

                    // Slide the window through the rest of the vector
                    for (int i = window_option; i < numbers.size(); ++i) {
                        // Add new element entering the window
                        filter.add_value(numbers[i]);
                        // Remove element leaving the window
                        filter.remove_value(numbers[i - window_option]);
                        // Calculate and store median of current window
                        results.push_back(filter.find_median());
                    }
                    
                    cout << "Your median values are: " << endl;
                    for (int i = 0; i < results.size(); ++i) {
                        cout << results[i] << endl;
                    }
                    cout << endl;
                    cout << "End of median results read out." << endl;

                    bool is_sub_option_active = true; // value for sub menu while loop 

                    while (is_sub_option_active) {
                        cout << endl;
                        cout << "Sub Menu:" << endl;
                        cout << endl;
                        cout << "1) Run an average filter on the same numbers." << endl;
                        cout << "2) Review your randomly generated values." << endl;

                        string sub_menu_option = "";
                        cout << endl << "Enter menu selection (Q to Main Menu): " << endl;
                        cin >> sub_menu_option;

                        if (sub_menu_option == "1") {
                            cout << endl;
                            cout << "Your averages are: " << endl;
                            for (int i = 0; i < numbers.size() - window_option + 1; ++i) {
                                double sum = 0;
                                for (int j = 0; j < window_option; j++) {
                                    sum = sum + numbers[i + j];
                                }
                                double result = sum / window_option;
                                cout << result << endl;
                            }
                            cout << endl;
                            cout << "End of average results read out." << endl;
                            cout << endl;

                        } else if (sub_menu_option == "2") {
                            cout << endl;
                            cout << "Your randomly generated numbers are:" << endl;
                            for (int i = 0; i < numbers.size(); ++i) {
                                cout << numbers[i] << endl;
                            }
                            cout << endl;
                            cout << "End of randomly generate numbers read out." << endl;
                        } else if (sub_menu_option == "Q") {
                            is_sub_option_active = false;
                            is_option_active = false;
                        }
                    }
                }
            }
        }
    }

    return 0;
}
