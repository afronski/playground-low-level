#include <iostream>

long long mod_exp(long long base, long long exponent, long long modulus) {
  long long test;

  for (test = 1; exponent; exponent >>= 1) {
    if (exponent & 1) {
        test = (test * base) % modulus;
    }

    base = (base * base) % modulus;
  }

  return test;
}

int main() {
  std::ios_base::sync_with_stdio(0);

  int n = 0;

  std::cin >> n;

  for (int i = 0; i < n; ++i) {
    long long base;
    long long exponent;

    std::cin >> base >> exponent;
    std::cout << mod_exp(base, exponent, 10) % 10 << std::endl;
  }

  return 0;
}