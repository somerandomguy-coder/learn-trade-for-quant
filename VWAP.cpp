#include "types.hpp"
#include <iostream>
#include <vector>

// struct Trade {
//   double price;
//   double volume;
// };

struct RollingVWAP {
  double cumulative_dollar_volume = 0.0;
  double cumulative_volume = 0.0;

  // TODO: Accumulate price * volume and volume
  void update(double price, double volume) {
    if (volume < 0)
      return;
    cumulative_dollar_volume += price * volume;
    cumulative_volume += volume;
  }

  // TODO: Return VWAP or 0.0 if cumulative_volume is 0
  double get_vwap() const {
    return cumulative_volume == 0
               ? 0.0
               : (cumulative_dollar_volume / cumulative_volume);
  }
};

int main() {
  RollingVWAP vwap_engine;

  // Stream of gold trades: {price, volume in lots}
  std::vector<Tick> trades = {
      {2650.00, 10.0}, // 10 lots at 2650.00
      {2650.50, 50.0}, // 50 lots at 2650.50 (heavy block buy)
      {2651.00, 5.0}   // 5 lots at 2651.00
  };

  for (size_t i = 0; i < trades.size(); ++i) {
    vwap_engine.update(trades[i].price, trades[i].volume);
    std::cout << "Trade " << i + 1 << " | Current VWAP: $"
              << vwap_engine.get_vwap() << "\n";
  }

  return 0;
}
