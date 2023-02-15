#include <iostream>
#include <cmath>
#include <chrono>
#include <string>
#include <numeric>
#include <algorithm>
#include "include/functions.h"

int main() {
    using namespace std::chrono_literals;
    uint64_t start_val = 0;
    uint64_t stop_val = 0;
    const int repeat_val = 10;
    uint64_t iteration_length_arr[repeat_val];
    long double avg_search_time = 0.0;
    uint64_t prime_count = 0;
    std::string choice;
    std::string yes_choices[] = {"Y", "y", "Yes", "yes"};
    std::string no_choices[] = {"N", "n", "No", "no"};

    std::cout << "Start prime_find? [Y/n]: ";
    std::cin >> choice;
    if (std::find(std::begin(yes_choices), std::end(yes_choices), choice) != std::end(yes_choices)) {
        while (true) {
            std::cout << "Enter an integer start value greater than 0 and less than 9223372036854775807 (aka 2^(64 - 1) - 1): ";
            std::cin >> start_val;
            if (start_val > 0 && start_val < std::numeric_limits<uint64_t>::max()) {
                break;
            } else {
                std::cerr << "Value out of range!" << '\n';
            }
        }
    
        while (true) {
            std::cout << "Enter an integer stop value greater than the start value and less than 9223372036854775807 (aka 2^(64 - 1) - 1): ";
            std::cin >> stop_val;
            if (stop_val > start_val && stop_val < std::numeric_limits<uint64_t>::max()) {
                break;
            } else {
                std::cerr << "Value out of range!" << '\n';
            }
        }

        std::cout << "Starting prime search..." << '\n';
        auto prog_start_time = std::chrono::steady_clock::now();

        for (int k = 0; k < repeat_val; k++) {
            std::cout << "Iteration " << (k + 1) << " of " << repeat_val << " Runtime (ns): ";
            auto iteration_start_time = std::chrono::steady_clock::now();
            for (uint64_t i = start_val; i < stop_val + 1; i++) {
                if (func::prime::is_prime(i)) {
                    prime_count++;
                }
            }
            auto iteration_stop_time = std::chrono::steady_clock::now();
            std::chrono::duration<uint64_t, std::nano> elapsed_single_iteration = iteration_stop_time - iteration_start_time; //how many nanoseconds have elapsed.
            iteration_length_arr[k] = elapsed_single_iteration.count(); //store elapsed_single_iteration nanoseconds in iteration_length_arr.
            std::cout << elapsed_single_iteration.count() << '\n';
        }

        avg_search_time = std::accumulate(std::begin(iteration_length_arr), std::end(iteration_length_arr), avg_search_time) / repeat_val;

        auto prog_stop_time = std::chrono::steady_clock::now();
        std::chrono::duration<uint64_t, std::nano> elapsed_prog_runtime = prog_stop_time - prog_start_time; //how many nanoseconds have elapsed.
        uint64_t prog_runtime_nanoseconds = elapsed_prog_runtime.count();

        std::cout << "Prime benchmark is done!" << '\n';

        std::cout << "\n**** Results ****" << '\n';
        std::cout << "Program ran for total of (DD:HH:MM:SS.SSSSSSSSS): " << func::to_days_hours_minutes_seconds(prog_runtime_nanoseconds) << '\n';
        std::cout << "\n";
        std::cout << "Program ran for: " << prog_runtime_nanoseconds << " ns" << '\n';
        std::cout << "\n";
        std::cout << "Average time to find all primes between " << start_val << " and " << stop_val << " was (DD:HH:MM:SS.SSSSSSSSS):" << '\n';
        std::cout << func::to_days_hours_minutes_seconds((uint64_t) avg_search_time) << '\n';
        std::cout << "\n";
        std::cout << "Average search time: " << (uint64_t) avg_search_time << " ns" << '\n';
        std::cout << "Number of primes found is: " << prime_count / repeat_val << '\n';
    } else if (std::find(std::begin(no_choices), std::end(no_choices), choice) != std::end(no_choices)) {
        std::cout << "Exited program." << '\n';
    } else if (!(std::find(std::begin(yes_choices), std::end(yes_choices), choice) != std::end(yes_choices)) && 
            !(std::find(std::begin(no_choices), std::end(no_choices), choice) != std::end(no_choices))) {
        std::cout << "Command not valid; please restart program and try again." << '\n';
    }
    
    return 0;
}
