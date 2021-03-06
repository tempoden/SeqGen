﻿#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"LFSR.h"
#include"NFSR.h"
#include"FuncReg.h"
#include"CombFuncReg.h"
#include"MixedFuncReg.h"
#include<map>
#include<stdlib.h>

bool f(std::vector<bool> val) {
	return (val[0] & val[1]) ^ (val[2] & val[3]) ^ (val[4] & val[5]) ^ (val[6] & val[7]) ^ (val[8] & val[9]) ^ (val[10] & val[11]);
}

bool f4(std::vector<bool> val) {
	return (val[0] & val[1]) ^ (val[2] & val[3]);
}

bool nonLin(std::vector<bool> x) {
	//return 1 ^ x[21] ^ (x[1] & x[2] & x[3] & x[4] & x[5] & x[6] & x[7] & x[8] & x[9] & x[10] & x[11] & x[12] & x[13] & x[14] & x[15] & x[16] & x[17] & x[18] & x[19] & x[20] & x[21]) ^ x[0];// x[3] ^ x[2] ^(x[2] & x[3]) ^ (x[1] & x[3]) ^ (x[1] & x[2]) ^ (x[1] & x[2] & x[3]) ^ x[0];
	return x[21] ^ (!x[1] & !x[2] & !x[3] & !x[4] & !x[5] & !x[6] & !x[7] & !x[8] & !x[9] & !x[10] & !x[11] & !x[12] & !x[13] & !x[14] & !x[15] & !x[16] & !x[17] & !x[18] & !x[19] & !x[20] & !x[21]) ^ x[0];
	//return 1 ^ x[1] ^ (x[1] & x[2] & x[3]) ^ x[0];
	//return  1 ^ x[1] ^ (x[1] & x[2]) ^ x[0];
}
//x8 & x12
//n=20 g+x4 | x18 полный
//n=22 g+x2

int main(int argc, char** argv) {

	freopen("out.txt","w",stdout);
	bool a = false;
	a ^= true;
	std::vector<bool> initial = { true,false,false,false,false,true,true,false,true,false,false,true };
	/*LFSR reg = LFSR(initial, {12,6,4,1});
	//FuncReg fr = FuncReg(reg, { false,false,false,true });
	FuncReg afr = FuncReg(reg, f);
	size_t count = 0;
	
	do {
		//std::cout << reg << std::endl;
		//reg.shift();
		count++;
		std::cout << afr;
		printf("%d\n",afr.shift());
	} while (afr.getReg().getState() != initial);
	std::cout << count;
	

	for (size_t i = 0; i < 1000; i++) {
		if (afr.shift())
			count++;
	}

	std::cout << count;
	
	
	std::map<std::vector<bool>, size_t> states;
	std::vector<size_t> pos = {0,5};
	std::vector<LSFR> regs = { LSFR({0,0,1,1,0,1},pos), LSFR({1,0,0,0,1,0},pos), LSFR({1,1,1,0,0,1}, pos), LSFR({0,1,1,0,0,0}, pos), LSFR({0,1,0,0,0,1}, pos), LSFR({1,1,1,1,1,1},pos) };
	CombFuncReg freg = CombFuncReg(regs,f6);
	for (size_t i = 0; i < 64; i++) {
		std::vector<LSFR> regs = freg.getRegs();
		std::cout << "Iteration " << i << std::endl;
		for(auto reg_ : regs) {
			std::cout << "\t" << reg_ << std::endl;
		}
		std::cout << "\tf(";
		for (auto reg_ : regs) {
			std::cout << reg_.getState()[0];
		}
		bool result = freg.shift();
		std::cout << ") = " << result << std::endl;
		if (result) count++;
		if (states.find(freg.getLast()) == states.end()) {
			states[freg.getLast()] = 0;
		}
		else {
			std::cout << "!!!Found cycle " << LSFR(freg.getLast(), {}) << " with length " << states[freg.getLast()]<<std::endl;
		}

		for (auto it : states) {
			states[it.first]++;
		}

		std::cout << states.size() << std::endl;

	}

	std::cout << "Amount of 1: " << count << std::endl;
	
	std::vector<LFSR> regs = {
		LFSR({0,1,0,1,1,1,1,1,1,1,0,0,0,1,0,1,1,0,0,1,1,1,0,0,0,1,1,0,1,0,0,0}, {32,22,2,1}),
		LFSR({1,0,1,1,1,0,1,0,1,0,0,0,1,1,1,1,1,1,0,1,0,1,0,0,1,0,0,1,1,1,0,1}, { 32,16,7,2 }),
		LFSR({0,0,0,0,1,1,1,0,1,1,1,0,0,1,0,1, 0,1,0,1,0,1,1,1, 1,0,1,1,1,0,0,1}, {32,30,17,12,3,1}),
		LFSR({1,1,0,1,1,1,1,1, 0,0,1,1,0,0,0,1, 1,0,0,0,0,0,0,1, 0,1,1,0,1,0,0}, {31,3})
	};
	CombFuncReg cfr = CombFuncReg(regs,f4);
	for (size_t i = 0; i < 536870912; i++) {
		size_t rly = 0;
		for (size_t j = 0; j < 8; j++) {
			rly <<= 4;
			rly += regs[0].shift()*8+regs[1].shift()*4+regs[2].shift()*2+regs[3].shift();
			//rly += cfr.shift();
		}
		
		unsigned char val =  0;
		unsigned char mask = 0xFE;

		for (size_t j = 0; j < 2; j++) {
			for (size_t k = 0; k < 4; k++) {
				val = (val << 1)&mask | regs[k].shift();
			}
		}

		std::cout << val;
	}
	*/

	NFSR nreg = NFSR({1,0,1}, nonLin);//{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1}, nonLin);

	std::cout << "Vector of function values" << std::endl;
	unsigned char m1 = 0x01, m2 = 0x02, m3 = 0x04, m4 = 0x08;
	for (unsigned char i = 0; i < 8; i++) {
		std::cout << static_cast<bool>(i&m3) << static_cast<bool>(i&m2) << static_cast<bool>(i&m1)<< "\t" <<nonLin({ static_cast<bool>(i&m3), static_cast<bool>(i&m2), static_cast<bool>(i&m1)})<<std::endl;
	}
	//std::cout << std::endl;

	//for (size_t i = 0; i < 524288; i++) {
	for (size_t i = 0; i < 65;i++) {
		//unsigned char wrt = 0;
		std::cout << nreg << std::endl;
		nreg.shift();
		//for (size_t j = 0; j < 8; j++) {
		//	wrt <<= 1;
		//	wrt += nreg.shift();
		//}
		//std::cout << wrt;
	}

	MixedFuncReg mfr = MixedFuncReg({ new LFSR(initial, {12,6,4,1}), new  NFSR({1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0}, nonLin),
		new LFSR({0,0,0,0,1,1,1,0,1,1,1,0,0,1,0,1, 0,1,0,1,0,1,1,1, 1,0,1,1,1,0,0,1}, {32,30,17,12,3,1}),
		new LFSR({1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,0}, {31,3}) },
		[](std::vector<bool> x) {return (bool)(x[0] & x[1] ^ x[2] & x[3]); });

	for (size_t i = 0; i < 297364;i++){	
		mfr.shift();
		//unsigned char toOut = 0;
		//for (size_t j = 0; j < 2; j++) {
			//toOut = (toOut<<1)|
		//	mfr.shift();
			//for (size_t k = 0; k < 4; k++){
				//toOut = (toOut << 1) | mfr.getState()[k];
			//}
		//}
		//std::cout << toOut;
		std::cout << LFSR(mfr.getState(), { 0 }) << std::endl;
	}

	return 0;
}