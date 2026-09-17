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

struct Tick {
  double price;
  double volume;
};

struct Bar {
  double open;
  double high;
  double low;
  double close;
  double volume;
};

enum class Side { BUY, SELL };
