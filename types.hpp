#pragma once

struct Quote {
  double bid;
  double ask;
};

struct Level1Quote {
  double bid_price;
  double bid_size;
  double ask_price;
  double ask_size;
};

enum class Side { BUY, SELL };
