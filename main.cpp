#include "types.hpp"
#include <iostream>

struct SlippageReport {
  double mid_price;
  double slippage_dollars;
  double slippage_bps;
};

double get_mid_price(Quote q) { return (q.ask + q.bid) / 2.0; };

SlippageReport calculate_slippage(Quote quote_at_signal, Side side,
                                  double fill_price) {
  SlippageReport report = {};
  double expected_price = get_mid_price(quote_at_signal);
  double slippage_dollars;
  if (side == Side::BUY) {
    slippage_dollars = fill_price - expected_price;
  } else {
    slippage_dollars = expected_price - fill_price;
  }

  report.mid_price = expected_price;
  report.slippage_dollars = slippage_dollars;
  report.slippage_bps = (slippage_dollars / expected_price) * 10000;

  return report;
};

int main() {
  Quote gold{2650.10, 2650.40};

  // Schenatio: We sent a BUY order when mid was 2650.23, but filled at 2650.45
  // (adverse slippage)
  double buy_fill = 2650.45;

  SlippageReport buy_rep = calculate_slippage(gold, Side::BUY, buy_fill);

  std::cout << "[BUY Order Execution]\n";
  std::cout << "Mid at signal:  $" << buy_rep.mid_price << "\n";
  std::cout << "Fill price:     $" << buy_fill << "\n";
  std::cout << "Slippage ($)    $" << buy_rep.slippage_dollars << "\n";
  std::cout << "Slippage (bps)  " << buy_rep.slippage_bps << "\n\n";

  // Schenatio: We sent a SELL order when mid was 2650.25, but filled at 2650.15
  double sell_fill = 2650.15;

  SlippageReport sell_rep = calculate_slippage(gold, Side::SELL, sell_fill);

  std::cout << "[SELL Order Execution]\n";
  std::cout << "Mid at signal:  $" << sell_rep.mid_price << "\n";
  std::cout << "Fill price:     $" << sell_fill << "\n";
  std::cout << "Slippage ($)    $" << sell_rep.slippage_dollars << "\n";
  std::cout << "Slippage (bps)  " << sell_rep.slippage_bps << "\n";

  return 0;
}
