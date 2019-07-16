#include"NFSR.h"
bool NFSR::shift() {
	bool pop = state[0];
	bool new_first = _f(state);
	for (size_t i = 1; i < size; i++) {
		state[i - 1] = state[i];
	}
	state[size - 1] = new_first;
	return pop;
}

void NFSR::setState(size_t new_state) {
	for (size_t i = 0; i < size; i++) {
		state[i] = (new_state & (1 << (size - i - 1)));
	}
}

std::ostream& operator<<(std::ostream &os, const NFSR &obj) {
	std::vector<bool> toOut = obj.getState();
	for (bool val : toOut) {
		os << val;
	}
	return os;
}