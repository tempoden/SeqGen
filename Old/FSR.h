#pragma once
#include<vector>
class FSR {
public:
	virtual ~FSR() {};
	virtual bool shift() = 0;
	virtual void setState(size_t new_state) = 0;
	virtual void setState(std::vector<bool> new_state) = 0;
	virtual std::vector<bool> getState() const = 0;
};