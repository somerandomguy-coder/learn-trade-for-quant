#include "types.hpp"
#include "vector"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>

struct TickBuffer {
  std::vector<double> buffer;
  size_t capacity;
  size_t head = 0;
  size_t count = 0;

  explicit TickBuffer(size_t limit) : capacity(limit), buffer(limit, 0.0) {
    if (capacity == 0) {
      std::cerr << "Capacity must be greater than 0\n";
      std::abort();
    }
  }

  // TickBuffer(int limit) {
  //   if (limit <= 0) {
  //     std::cerr << "can't have buffer with size lower than zero\n";
  //     std::abort();
  //   }

  //   capacity = limit;
  //   buffer = std::vector<double>(0, limit * 2);
  // };

  double average() const {
    double sum = std::accumulate(buffer.begin(), buffer.begin() + count, 0.0);

    return sum / static_cast<double>(count);

    // for (auto it = buffer.begin() + head; it < buffer.end(); it++) {
    //   sum += *it;
    // }
    // if there's only 1, 2 or 3 element it would use the actual size
    // double average = sum / std::min(capacity, count);
    // return average;
  };

  void push(double price) {
    buffer[head] = price;
    head = (head + 1) % capacity;
    if (count < capacity) {
      ++count;
    }
  }
};

int main() {
  // A moving buffer tracking the last 3 ticks of Gold
  TickBuffer ticks(3);

  ticks.push(2650.10);
  std::cout << "After 1 tick  | Count: " << ticks.count
            << " | Avg: " << ticks.average() << "\n";

  ticks.push(2650.30);
  std::cout << "After 2 ticks | Count: " << ticks.count
            << " | Avg: " << ticks.average() << "\n";

  ticks.push(2650.80);
  std::cout << "After 3 ticks | Count: " << ticks.count
            << " | Avg: " << ticks.average() << "\n";

  // 4th tick: overwrites the oldest (2650.10), buffer now holds [2650.30,
  // 2650.80, 2651.00]
  ticks.push(2651.00);
  std::cout << "After 4 ticks | Count: " << ticks.count
            << " | Avg: " << ticks.average() << "\n";

  return 0;
}
