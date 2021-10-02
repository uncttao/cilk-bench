#include <iostream>
#include <ctime>
#include <cilk/cilk.h>
#include <cstdlib>

int64_t fib(int64_t n) {
  if (n < 2) return n;
  int x, y;
  x = cilk_spawn fib(n - 1);
  y = fib(n - 2);
  cilk_sync;
  return x + y;
}

int64_t rsum(int64_t m, int64_t n) {
  if (m == n) {
    return m;
  } else {
    auto mid = m + (n - m) / 2;
    long left;
    long right;
    long sum;

    left = cilk_spawn rsum(m, mid);
    right = rsum(mid + 1, n);
    cilk_sync;

    sum = left + right;

    return sum;
  }
}

int main(int argc, char *argv[]) {
  auto input = atoi(argv[1]);

  auto result = fib(input);
  //auto result = rsum(0, input);

  std::cout << result << std::endl;

  return 0;
}

