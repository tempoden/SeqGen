#include<iostream>
#include<map>
#include<stdlib.h>
#include"LFSR.h"
#include"NFSR.h"
#include"FuncReg.h"



std::map<unsigned char, unsigned char> S = { {0x0,0xC}, {0x1,0x5}, {0x2,0x6}, {0x3,0xB}, {0x4,0x9}, {0x5,0x0}, {0x6,0xA}, {0x7,0xD},
									   	     {0x8,0x3}, {0x9,0xE}, {0xA,0xF}, {0xB,0x8}, {0xC,0x4}, {0xD,0x7}, {0xE,0x1}, {0xF,0x2} };

std::vector<bool> values = { 0,1,1,0,1,0,0,1,0,0,1,1,1,1,0,0,0,0,0,0,1,1,0,1,0,1,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1,0,1,0,0,1,1,
	1,0,0,1,0,1,0,0,0,1,0,0,1,1,1,0,1,1,0,1,0,1,0,1,1,0,0,1,0,0,0,1,1,0,0,0,1,1,1,1,0,0,1,0,1,0,0,1,0,0,0,0,1,1,0,0,1,0,1,1,1,1,
	1,1,0,1,1,0,0,0,1,0,0,1,1,0,0,1,1,0,0,1,0,1,0,0,0,1,1,0,1,0,1,0,0,1,1,0,1,0,1,1,1,0,0,1,1,0,0,1,0,1,1,0,1,0,1,1,1,0,0,1,0,1,
	0,1,1,0,0,1,0,1,0,0,1,0,0,1,0,1,1,0,1,0,1,1,0,1,0,1,0,1,0,0,1,1,1,0,0,1,0,0,1,0,1,0,0,1,1,1,0,0,0,1,0,1,1,0,1,0,0,0,1,0,0,1,
	0,0,1,1,0,1,1,0,0,1,1,1,1,0,1,0,1,1,0,0 };

bool feedback_(std::vector<bool> x) {
	size_t index = 0;
	for (size_t i = 0; i < x.size(); i++) {
		index <<= 1;
		if (x[i]) {
			index++;
		}
	}
	return values[index];
}

bool feedback(std::vector<bool> x) {
	return feedback_({ x[0],x[8],x[9],x[16],x[17],x[24],x[27],x[28] });
}

int main() {
	// freopen("super.txt", "w", stdout);
	LFSR linear = LFSR({ 0,0,0,0,1,1,1,0,1,1,1,0,0,1,0,1, 0,1,0,1,0,1,1,1, 1,0,1,1,1,0,0,1 }, { 32,30,17,12,3,1 });
	NFSR non_linear = NFSR({ 1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1 },
		[](std::vector<bool> x) {return (bool)(x[0] ^ x[1] ^ x[2] ^ x[5] ^ x[10] ^ x[13] ^ x[15] ^ x[24] ^ x[26]
			^ x[7] & x[22] ^ x[11] & x[18] ^ x[13] & x[19] ^ x[16] & x[25] ^ x[24] & x[25] ^ x[15] & x[25] & x[26] ^
			x[8] & x[10] & x[25] & x[26]); });
	FuncReg freg = FuncReg(LFSR({ 1,0,1,1,1,0,1,0,1,0,0,0,1,1,1,1,1,1,0,1,0,1,0,0,1,0,0,1,1,1,0,1 }, { 32,16,7,2 }),
		feedback
	);

	for (size_t i = 0; i < 6553600; i++) {
		unsigned char result = 0;
		for (size_t j = 0; j < 2; j++) {
			result <<= 4;
			unsigned char a = 0;
			for (size_t k = 0; k < 4; k++){
				a <<= 1;
#ifdef LINEAR_XOR
				a |= (linear.shift() ^ freg.shift());
#else
#ifdef NON_LINEAR
				a |= non_linear.shift();
#else
				a |= (linear.shift() ^ non_linear.shift() ^ freg.shift());
#endif
#endif
			}
#ifdef S_BLOCK
			result |= S[a];
#else
			result |= a;
#endif
		}
		std::cout << result;
	}

	return 0;
}
