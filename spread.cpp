#include <iostream>

struct Quote {
  double bid;
  double ask;
};

double get_spread(Quote q) { return q.ask - q.bid; };

double get_mid_price(Quote q) { return (q.ask + q.bid) / 2.0; };

// me homework
bool can_trade(Quote q, double max_spread) {
  return get_spread(q) < max_spread;
};

int main() {
  Quote gold;
  gold.bid = 2000.0;
  gold.ask = 2000.5;
  double threadhold = 10;

  double spread = get_spread(gold);
  double mid = get_mid_price(gold);

  bool will_trade = can_trade(gold, threadhold);

  // Print the results to the terminal
  std::cout << "Gold Bid:           $" << gold.bid << "\n";
  std::cout << "Gold Ask:           $" << gold.ask << "\n";
  std::cout << "Spread:             $" << spread << "\n";
  std::cout << "Mid Price:          $" << mid << "\n";
  std::cout << "Would we trade:     " << will_trade << "\n";

  Quote Bitcoin;
  Bitcoin.bid = 1000;
  Bitcoin.ask = 1011;

  will_trade = can_trade(Bitcoin, threadhold);
  std::cout << "Would we trade:     " << will_trade << "\n";

  return 0;
}
