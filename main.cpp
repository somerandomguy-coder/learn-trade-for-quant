#include "types.hpp"
#include "vector"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

struct TickBuffer {
  std::vector<double> buffer;
  size_t capacity;
  size_t head = 0;
  size_t count = 0;

  TickBuffer(int limit) {
    if (limit <= 0) {
      std::cerr << "can't have buffer with size lower than zero\n";
      std::abort();
    }

    capacity = limit;
    buffer = std::vector<double>(0, limit * 2);
  };

  double average() {
    double sum = 0;

    for (auto it = buffer.begin() + head; it < buffer.end(); it++) {
      // std::cout << "*it: " << *it << "\n";
      sum += *it;
    }
    // if there's only 1, 2 or 3 element it would use the actual size
    double average = sum / std::min(capacity, count);
    // std::cout << "sum: " << sum << "\n";
    // std::cout << "size: " << std::min(capacity, count) << "\n";
    // std::cout << "average: " << average << "\n";
    return average;
  };

  void push(double e) {
    buffer.push_back(e);
    count++;
    head = std::max(int(count) - int(capacity), 0);
    // std::cout << "head: " << head << "\n";
  }
};

int main() {
  std::cout << "Hello, World!\n";
  TickBuffer ring(3);
  ring.push(1);
  ring.push(2);
  std::cout << "average: " << ring.average() << "\n";
  ring.push(3);
  std::cout << "average: " << ring.average() << "\n";
  ring.push(4);
  std::cout << "average: " << ring.average() << "\n";
  ring.push(5);
  std::cout << "average: " << ring.average() << "\n";
  ring.push(5);
  std::cout << "average: " << ring.average() << "\n";
  ring.push(5);
  std::cout << "average: " << ring.average() << "\n";
  return 0;
}
