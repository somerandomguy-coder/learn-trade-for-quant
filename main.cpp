#include <cstdint>
#include <deque>
#include <iostream>

struct Order {
  uint64_t id;
  double remaining_size;
};

struct PriceLevelQueue {
  std::deque<Order> orders;

  void add_order(uint64_t id, double lots) {
    if (lots == 0)
      return;
    orders.push_back({id, lots});
  };

  double match_market_order(double lots) {
    if (orders.empty())
      return 0;

    double order_matched = 0.0;
    while (!orders.empty()) {
      Order front = orders.front();
      orders.pop_front();

      if (lots >= front.remaining_size) {
        lots -= front.remaining_size;
        order_matched += front.remaining_size;
      } else {
        front.remaining_size -= lots;
        orders.push_front(front);
        order_matched += lots;
        return order_matched;
      }
    }

    return order_matched;
  };

  size_t order_count() { return orders.size(); }

  size_t order_depth() {
    size_t count = 0;
    for (auto const &order : orders) {
      count += order.remaining_size;
    }

    return count;
  };
};

int main() {
  // Resting bids at price $2650.00
  PriceLevelQueue best_bid_level;

  best_bid_level.add_order(101, 10.0); // First in line (10 lots)
  best_bid_level.add_order(102, 25.0); // Second in line (25 lots)
  best_bid_level.add_order(103, 15.0); // Third in line (15 lots)

  std::cout << "Starting resting orders: " << best_bid_level.order_count()
            << "\n\n";

  // Scenario 1: A market sell order arrives for 15 lots
  // Fills order 101 completely (10 lots) and takes 5 lots from order 102
  double filled_1 = best_bid_level.match_market_order(15.0);
  std::cout << "Market Order 1 (size 15.0) matched: " << filled_1 << " lots\n";
  std::cout << "Remaining resting orders: " << best_bid_level.order_count()
            << " (Front order ID " << best_bid_level.orders.front().id
            << " has " << best_bid_level.orders.front().remaining_size
            << " lots left)\n\n";

  // Scenario 2: A large market sell order arrives for 50 lots
  // Should clear the rest of 102 (20 lots) and all of 103 (15 lots), exhausting
  // the book
  double filled_2 = best_bid_level.match_market_order(50.0);
  std::cout << "Market Order 2 (size 50.0) matched: " << filled_2 << " lots\n";
  std::cout << "Remaining resting orders: " << best_bid_level.order_count()
            << "\n";

  return 0;
}
