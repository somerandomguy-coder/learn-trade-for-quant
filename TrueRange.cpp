#include "types.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

struct TrueRangeCalculator {
  double prev_close = 0.0;
  bool is_initialized = false;

  TrueRangeCalculator() = default;

  double calculate_tr(const Bar &bar) {
    double true_range = bar.high - bar.low;

    if (!is_initialized) {
      is_initialized = true;
    } else {
      true_range = std::max(true_range, std::abs(bar.high - prev_close));
      true_range = std::max(true_range, std::abs(bar.low - prev_close));
    }

    prev_close = bar.close;
    return true_range;
  };
};

int main() {
  TrueRangeCalculator tr_calc;

  // Scenario: Gold bars with a weekend/news gap
  // Bar 1: Normal bar (2650 -> 2655)
  // Bar 2: Gap up! Opens at 2660, high 2662, low 2659, close 2661
  //        Notice high-low is only $3.00, but from prev close (2655) to high
  //        (2662) is $7.00!
  std::vector<Bar> bars = {
      {2650.0, 2655.0, 2648.0, 2654.0}, // Bar 1: high-low = 7.0
      {2660.0, 2662.0, 2659.0,
       2661.0}, // Bar 2: gap up from 2654.0 -> TR should be 8.0 (2662 - 2654)
      {2658.0, 2660.0, 2652.0, 2653.0}
      // Bar 3: high-low = 8.0, gap down from 2661 to 2652 = 9.0
  };

  for (size_t i = 0; i < bars.size(); ++i) {
    double tr = tr_calc.calculate_tr(bars[i]);
    std::cout << "Bar " << i + 1 << " | True Range: $" << tr << "\n";
  }

  return 0;
}
