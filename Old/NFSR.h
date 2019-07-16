#pragma once
#include"FSR.h"
#include<iostream>
class NFSR : public FSR {
	size_t size;
	bool(*_f)(std::vector<bool>);
	std::vector<bool> state;
public:
	NFSR() {}
	NFSR(size_t reg_size, std::vector<bool> initial_state, bool(*feedback)(std::vector<bool>)) {
		size = reg_size;
		state = initial_state;
		_f = feedback;
	};
	NFSR(std::vector<bool> initial_state, bool(*feedback)(std::vector<bool>)) {
		size = initial_state.size();
		state = initial_state;
		_f = feedback;
	};
	NFSR(size_t reg_size, bool(*feedback)(std::vector<bool>)) {
		size = reg_size;
		state = std::vector<bool>(size);
		_f = feedback;
	};
	~NFSR() {};
	bool(*getFeedbackFunction(void))(std::vector<bool>){
		return _f;
	}
	void setFeedbackFunction(bool(*feedback)(std::vector<bool>)) { _f = feedback;  };
	void setState(size_t new_state) override;
	void setState(std::vector<bool> new_state) override { state = new_state; };
	std::vector<bool> getState() const override { return state; };
	bool shift() override;
};

std::ostream& operator<<(std::ostream &os, const NFSR &obj);