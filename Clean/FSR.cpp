#include"FSR.h"

bool FSR::shift() {
  auto pop = state[0];
  auto new_first = _f(state);
  for (size_t i = 1; i < size; i++) {
    state[i - 1] = state[i];
  }
  state[size - 1] = new_first;
  return pop;
}

std::ostream& operator<<(std::ostream &os, const FSR &obj) {
  auto toOut = obj.getState();
  for (bool val : toOut) {
    os << val;
  }
  return os;
}
