#include "types.hpp"
#include <iostream>

struct SimplePosition {
  Side _side = Side::BUY;
  double _lots = 0;
  double _entry_price = 0;
  bool is_opened = false;

  SimplePosition() = default;

  void open_position(Side side, double lots, double fill_price) {
    if (lots <= 0 || fill_price <= 0) {
      std::cerr << "lots or fill_price have to be positive";
    }
    _side = side;
    _lots = lots;
    _entry_price = fill_price;
    is_opened = true;
  }

  double close_position(double exit_price, double contract_multiplier) {
    if (!is_opened || _lots <= 0 || contract_multiplier <= 0) {
      return 0.0;
    }
    double profit_loss;
    profit_loss = (exit_price - _entry_price) * _lots * contract_multiplier;

    if (_side == Side::SELL) {
      profit_loss *= -1;
    }

    // reset the state
    is_opened = false;
    _side = Side::BUY;
    _lots = 0.0;
    _entry_price = 0.0;

    return profit_loss;
  }
};

int main() {
  // Standard Gold contract multiplier (100 oz / lot)
  const double COMEX_GC_MULT = 100.0;

  SimplePosition pos;

  // Trade 1: Long Gold (BUY 0.5 lots at 2650.00, close at 2654.50 -> +$4.50
  // move)
  pos.open_position(Side::BUY, 0.5, 2650.00);
  double pnl1 = pos.close_position(2654.50, COMEX_GC_MULT);
  // Expected: 4.50 * 0.5 * 100 = +$225.00
  std::cout << "Trade 1 Realized P&L: $" << pnl1 << "\n";

  // Trade 2: Short Gold (SELL 1.0 lot at 2660.00, close at 2662.00 -> -$2.00
  // loss)
  pos.open_position(Side::SELL, 1.0, 2660.00);
  double pnl2 = pos.close_position(2662.00, COMEX_GC_MULT);
  // Expected: (2660.00 - 2662.00) * 1.0 * 100 = -$200.00
  std::cout << "Trade 2 Realized P&L: $" << pnl2 << "\n";

  return 0;
}
