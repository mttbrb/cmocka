#include "silly_math.h"

int mult(int x, int y) {
  return x * y;
}

int sub(int x,int y) {
  return x - y;
}

int add(int x, int y) {
  return x + y;
}

int div(int x, int y) {
  if (!y) return 0;
  return x / y;
}
