#include <algorithm>
#include <iostream>
#include <optional>
#include <vector>
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

struct VolumeBarBuilder {
  double open = 0.0;
  double high = 0.0;
  double low = 0.0;
  double close = 0.0;
  double current_volume = 0.0;
  double volume_threshold;
  bool is_building = false;

  VolumeBarBuilder(double threshold) : volume_threshold(threshold) {};

  std::optional<Bar> process_tick(const Tick &tick) {
    if (!is_building) {
      current_volume = tick.volume;
      open = tick.price;
      close = tick.price;
      high = tick.price;
      low = tick.price;
      is_building = true;

    } else {
      high = std::max(high, tick.price);
      low = std::min(low, tick.price);
      current_volume += tick.volume;
      if (current_volume >= volume_threshold) {
        close = tick.price;
        is_building = false;
        return Bar{open, high, low, close, current_volume};
      };
    }
    return std::nullopt;
  }
};

int main() {
  // Build a bar every time 50.0 lots/units of gold are traded
  VolumeBarBuilder builder(50.0);

  std::vector<Tick> stream = {
      {2650.00, 20.0}, // Total: 20 -> in progress
      {2650.50, 15.0}, // Total: 35 -> in progress
      {2649.80, 25.0}, // Total: 60 -> hits threshold! Bar 1 complete.
      {2651.00, 30.0}, // Total: 30 -> in progress
      {2651.20, 25.0}  // Total: 55 -> hits threshold! Bar 2 complete.
  };

  int bar_count = 1;
  for (const auto &tick : stream) {
    std::optional<Bar> completed_bar = builder.process_tick(tick);
    if (completed_bar.has_value()) {
      std::cout << "[Bar " << bar_count++ << " Closed]\n"
                << "  Open:   " << completed_bar->open << "\n"
                << "  High:   " << completed_bar->high << "\n"
                << "  Low:    " << completed_bar->low << "\n"
                << "  Close:  " << completed_bar->close << "\n"
                << "  Volume: " << completed_bar->volume << "\n\n";
    }
  }

  return 0;
}
