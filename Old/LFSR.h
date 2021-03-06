#pragma once
#include"FSR.h"
#include<iostream>
//LSFR stands for " linear feedback shift register"

std::vector<size_t> getPos(std::vector<size_t> deg_list, size_t deg);

class LFSR : public FSR{
	size_t size;
	std::vector<size_t> pos;
	std::vector<bool> state; 
public:
	LFSR(){}
	LFSR(size_t reg_size, std::vector<bool> initial_state ,std::vector<size_t> pos_list) {
		size = reg_size;
		state = initial_state;
		pos = getPos(pos_list, size);
	};
	LFSR(size_t reg_size, std::vector<size_t> pos_list) {
		size = reg_size;
		state = std::vector<bool>(size);
		pos = getPos(pos_list, size);
	}
	LFSR(std::vector<bool> initial_state, std::vector<size_t> pos_list) {
		size = initial_state.size();
		state = initial_state;
		pos = getPos(pos_list, size);
	};
	~LFSR() {};
	void setState(size_t new_state) override;
	void setState(std::vector<bool> new_state) override { state = new_state; };
	std::vector<bool> getState() const override { return state; };
	bool shift() override;
};

std::ostream& operator<<(std::ostream &os, const LFSR &obj);
