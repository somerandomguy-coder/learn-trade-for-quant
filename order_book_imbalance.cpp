#include "types.hpp"
#include <cassert>
#include <iostream>

double calculate_imbalance(const Level1Quote &q) {
  double total = q.bid_size + q.ask_size;
  if (total <= 0) {
    return 0.0;
  }

  double order_book_imbalance = (q.bid_size - q.ask_size) / total;

  return order_book_imbalance;
};

int main() {
  // Heavy buying pressure (bid size >> ask size)
  Level1Quote buy_pressure{2650.10, 50.0, 2650.30, 10.0};
  std::cout << "Buy Heavy Imbalance:  " << calculate_imbalance(buy_pressure)
            << "\n"; // Expected: +0.6667

  // Heavy selling pressure (ask size >> bid size)
  Level1Quote sell_pressure{2650.10, 5.0, 2650.30, 45.0};
  std::cout << "Sell Heavy Imbalance: " << calculate_imbalance(sell_pressure)
            << "\n"; // Expected: -0.8

  // Balanced book
  Level1Quote balanced{2650.10, 20.0, 2650.30, 20.0};
  std::cout << "Balanced Imbalance:   " << calculate_imbalance(balanced)
            << "\n"; // Expected: 0.0

  return 0;
}
