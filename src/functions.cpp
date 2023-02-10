#include "include/functions.h"
#include <cmath>
#include <string>
#include <numeric>
#include <sstream>
#include <iomanip>
#include <algorithm>

namespace func {

    namespace prime {

        bool is_prime(int64_t n) {
            if (n <= 1) {
                return false;
            } else if (n == 2) {
                return true;
            } else if (n > 2 && n % 2 == 0) {
                return false;
            }

            int64_t max_divisor = std::floor(std::sqrt((double) n));
            for (int64_t d = 3; d < max_divisor + 1; d+=2) {
                if (n % d == 0) {
                    return false;
                }
            }

            return true;
        }
    }

    std::string to_days_hours_minutes_seconds(int64_t nanoseconds) {
        constexpr uint64_t ns_in_day = 86400000000000;
        constexpr uint64_t ns_in_hour = 3600000000000;
        constexpr uint64_t ns_in_min = 60000000000;
    
        auto days = nanoseconds / ns_in_day;
        nanoseconds = nanoseconds - (days * ns_in_day);
    
        auto hours = nanoseconds / ns_in_hour;
        nanoseconds = nanoseconds - (hours * ns_in_hour);
    
        auto minutes = nanoseconds / ns_in_min;
        nanoseconds = nanoseconds - (minutes * ns_in_min);
    
        auto seconds = nanoseconds / 1000000000;
        nanoseconds = nanoseconds - (seconds * 1000000000);
    
        auto nanosecs = nanoseconds;
    
        return zero_padded_num(std::to_string(days), 2) + ":" +
        zero_padded_num(std::to_string(hours), 2) + ":" +
        zero_padded_num(std::to_string(minutes), 2) + ":" +
        zero_padded_num(std::to_string(seconds), 2) + "." +
        zero_padded_num(std::to_string(nanosecs), 9);
    }

    std::string zero_padded_num(std::string str, size_t field_width) {
        int precision = field_width - std::min(field_width, str.size());
        return std::string(precision, '0').append(str);
    }

}