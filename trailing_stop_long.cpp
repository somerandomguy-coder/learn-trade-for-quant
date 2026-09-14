#include <iostream>
#include <vector>

struct TrailingStopLong {
  bool is_stopped_out = false;
  double highest_price;
  double trail_distance;
  double stop_price;

  TrailingStopLong(double entry_price, double trail_distance)
      : highest_price(entry_price), trail_distance(trail_distance),
        stop_price(entry_price - trail_distance) {};

  bool update(double current_price) {
    if (is_stopped_out) {
      return true;
    }

    if (current_price > highest_price) {
      highest_price = current_price;
      stop_price = highest_price - trail_distance;
    } else if (current_price <= stop_price) {
      is_stopped_out = true;
    }

    return is_stopped_out;
  };
};

int main() {
  // Bought Gold at 2650.00 with a $2.00 trailing stop (initial stop at 2648.00)
  TrailingStopLong tracker(2650.00, 2.00);

  std::vector<double> price_stream = {
      2651.00, // New high -> Stop ratchets to 2649.00
      2653.50, // New high -> Stop ratchets to 2651.50
      2652.00, // Pullback -> Stop remains 2651.50 (Safe)
      2651.40  // Breaches 2651.50 -> Stop triggered!
  };

  for (double price : price_stream) {
    bool triggered = tracker.update(price);
    std::cout << "Price: " << price << " | Peak: " << tracker.highest_price
              << " | Stop: " << tracker.stop_price
              << " | Triggered: " << (triggered ? "YES (EXIT)" : "NO") << "\n";
    if (triggered)
      break;
  }

  return 0;
}
