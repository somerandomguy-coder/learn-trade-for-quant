#include "vector"
#include <iostream>

struct StreamingEMA {
  size_t period;
  double alpha;
  double current_ema;
  bool is_initialized = false;

  explicit StreamingEMA(size_t p) : alpha(2.0 / (p + 1)), period(p) {};

  double update(double price) {
    if (!is_initialized) {
      current_ema = price;
      is_initialized = true;
    } else {
      current_ema = alpha * price + (1 - alpha) * current_ema;
    }

    return current_ema;
  }
};

int main() {
  // 3-period EMA tracker on Gold close prices
  StreamingEMA ema3(3); // alpha = 2 / (3 + 1) = 0.5

  std::vector<double> prices = {2650.0, 2652.0, 2651.0, 2655.0};

  // Expected progression:
  // Tick 1 (2650.0): Seed -> 2650.0
  // Tick 2 (2652.0): 0.5 * 2652.0 + 0.5 * 2650.0 = 2651.0
  // Tick 3 (2651.0): 0.5 * 2651.0 + 0.5 * 2651.0 = 2651.0
  // Tick 4 (2655.0): 0.5 * 2655.0 + 0.5 * 2651.0 = 2653.0

  for (size_t i = 0; i < prices.size(); ++i) {
    double result = ema3.update(prices[i]);
    std::cout << "Step " << i + 1 << " | Price: " << prices[i]
              << " | EMA: " << result << "\n";
  }

  return 0;
}
