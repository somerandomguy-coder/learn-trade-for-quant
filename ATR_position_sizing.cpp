#include <cmath>
#include <cstdlib>
#include <iostream>

struct SizingParams {
  double equity;
  double risk_pct;
  double entry_price;
  double stop_price;
  double contract_mult;
  double min_lots = 0.01;
  double max_lots = 10;
  double lots_step = 0.01;
};

double calculate_position_size(const SizingParams &p) {
  if (p.equity <= 0 || p.risk_pct <= 0 || p.contract_mult <= 0 ||
      p.lots_step == 0 || p.entry_price <= p.stop_price)
    return 0;
  double acceptable_risk = p.equity * p.risk_pct;

  double stop_distance = std::abs(p.entry_price - p.stop_price);
  double risk_per_loss = stop_distance * p.contract_mult;

  if (acceptable_risk > risk_per_loss * p.max_lots) {
    return p.max_lots;
  } else if (acceptable_risk < risk_per_loss * p.min_lots) {
    return 0.0;
  }

  double smallest_risk_division = risk_per_loss * p.lots_step;
  acceptable_risk = std::floor(acceptable_risk / smallest_risk_division) *
                    smallest_risk_division;

  return acceptable_risk / risk_per_loss;
}

int main() {
  // Account: $10,000 | 1% risk ($100) | COMEX Gold (100 oz/lot)
  // Entry: $2650.00 | Stop: $2645.00 (Risk: $5.00/oz -> $500 per full lot)
  SizingParams params{
      10000.0, // equity
      0.01,    // 1% risk ($100 max risk)
      2650.0,  // entry
      2645.0,  // stop ($5 stop distance)
      100.0,   // COMEX 100 oz multiplier
      0.01,    // min lot
      10.0,    // max lot
      0.01     // lot step
  };

  double lots = calculate_position_size(params);
  // Expected: $100 / $500 = 0.20 lots
  std::cout << "Calculated Lot Size: " << lots << " lots\n";

  // Scenario 2: Volatility expands, wider stop required ($12.50 stop)
  params.stop_price = 2637.50; // $12.50 stop distance -> $1250 per lot
  // Expected: $100 / $1250 = 0.08 lots
  std::cout << "High Volatility Lot Size: " << calculate_position_size(params)
            << " lots\n";

  return 0;
}
