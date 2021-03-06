#pragma once
#include<iostream>
#include<vector>
class FSR {
  size_t size;
  bool(*_f)(std::vector<bool>);
  std::vector<bool> state;
public:
  FSR(){}
  FSR(std::vector<bool> initial_state, bool(*feedback)(std::vector<bool>)){
    size = initial_state.size();
    state = initial_state;
    _f = feedback;
  }
  ~FSR(){}
  void setState(std::vector<bool> new_state) { state = new_state; }
  std::vector<bool> getState() const { return state; }
  bool shift();
};

std::ostream &operator<<(std::ostream &os, const FSR &obj);
