﻿#include<iostream>
#include"CombFuncReg.h"
#include"FSR.h"
using namespace std;

std::vector<bool> values = {0,1,1,0,1,0,0,1,0,0,1,1,1,1,0,0,0,0,0,0,1,1,0,1,0,1,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1,0,1,0,0,1,1,
	1,0,0,1,0,1,0,0,0,1,0,0,1,1,1,0,1,1,0,1,0,1,0,1,1,0,0,1,0,0,0,1,1,0,0,0,1,1,1,1,0,0,1,0,1,0,0,1,0,0,0,0,1,1,0,0,1,0,1,1,1,1,
	1,1,0,1,1,0,0,0,1,0,0,1,1,0,0,1,1,0,0,1,0,1,0,0,0,1,1,0,1,0,1,0,0,1,1,0,1,0,1,1,1,0,0,1,1,0,0,1,0,1,1,0,1,0,1,1,1,0,0,1,0,1,
	0,1,1,0,0,1,0,1,0,0,1,0,0,1,0,1,1,0,1,0,1,1,0,1,0,1,0,1,0,0,1,1,1,0,0,1,0,0,1,0,1,0,0,1,1,1,0,0,0,1,0,1,1,0,1,0,0,0,1,0,0,1,
	0,0,1,1,0,1,1,0,0,1,1,1,1,0,1,0,1,1,0,0};

bool feedback(std::vector<bool> x){
	size_t index = 0;
	for(size_t i = 0; i < x.size(); i++){
		index<<=1;
		if(x[i]){
			index++;
		}
	}
	return values[index];
}


bool combFunc(vector<bool> x) {
  return bool(x[1] ^ x[2]);
}

//10010110110000110000011111011010101010100111000110110101010011000110011001001110111100010011100001011100001110011000100110100111111001011001000110011100001110100001110010001111011100100110011000110010101011011000111001010101010110111110000011000011011010010110000110011010100111100110011010011110011001010110000101101001000111101110010111100001000110011100001100111000011010011001111011100101000110110001101011010100100100100110110010011101101000110011110011000010011010011010011110010110100101110110011001011000


int main() {
  FSR LFSR1 = FSR(
    {1,0,1,1,1,0,1,0,1,0,0,0,1,1,1,1,1,1,0,1,0,1,0,0,1,0,0,1,1,1,0,1},
    [](vector<bool> x){return bool(x[1]^x[6]^x[15]^x[31]);});
  FSR LFSR2 = FSR(
    {0,1,0,1,1,1,1,1,1,1,0,0,0,1,0,1,1,0,0,1,1,1,0,0,0,1,1,0,1,0,0,0},
    [](vector<bool> x){return bool(x[0]^x[1]^x[21]^x[31]);});
  FSR LFSR3 = FSR(
    {0,0,0,0,1,1,1,0,1,1,1,0,0,1,0,1,0,1,0,1,0,1,1,1,1,0,1,1,1,0,0,1},
    [](vector<bool> x){return bool(x[0]^x[2]^x[11]^x[16]^x[29]^x[31]);});
  FSR NFSR = FSR(
    {1,1,0,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,1,0,1,1,0,1,0,0,1},
    feedback
    );
  CombFuncReg gen = CombFuncReg({LFSR1,LFSR2,LFSR3,NFSR},combFunc);

}