#include<cstdio>
#include<random>
#include<stdlib.h>

unsigned char values[] = { 0,1,1,0,1,0,0,1,0,0,1,1,1,1,0,0,0,0,0,0,1,1,0,1,0,1,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1,0,1,0,0,1,1,
	1,0,0,1,0,1,0,0,0,1,0,0,1,1,1,0,1,1,0,1,0,1,0,1,1,0,0,1,0,0,0,1,1,0,0,0,1,1,1,1,0,0,1,0,1,0,0,1,0,0,0,0,1,1,0,0,1,0,1,1,1,1,
	1,1,0,1,1,0,0,0,1,0,0,1,1,0,0,1,1,0,0,1,0,1,0,0,0,1,1,0,1,0,1,0,0,1,1,0,1,0,1,1,1,0,0,1,1,0,0,1,0,1,1,0,1,0,1,1,1,0,0,1,0,1,
	0,1,1,0,0,1,0,1,0,0,1,0,0,1,0,1,1,0,1,0,1,1,0,1,0,1,0,1,0,0,1,1,1,0,0,1,0,0,1,0,1,0,0,1,1,1,0,0,0,1,0,1,1,0,1,0,0,0,1,0,0,1,
	0,0,1,1,0,1,1,0,0,1,1,1,1,0,1,0,1,1,0,0 };

bool non_lin(uint32_t x) {
#define x(y) ((x>>y)&1)
	return x(0) ^ x(1) ^ x(2) ^ x(5) ^ x(10) ^ x(13) ^ x(15) ^ x(24) ^ x(26)
		^ x(7) & x(22) ^ x(11) & x(18) ^ x(13) & x(19) ^ x(16) & x(25) ^ x(24) & x(25) ^ x(15) & x(25) & x(26) ^
		x(8) & x(10) & x(25) & x(26);
#undef x
}

int main(int argc, char** argv) {

	//std::ios::sync_with_stdio(false);

	int seed = 123;
	
	std::mt19937 engine = std::mt19937(seed);
	std::uniform_int_distribution <> dis1{ 1, 2147483647 };

	uint32_t linear, nonlinear, filter;
	filter = 0b10111010100011111101010010011101;
	unsigned char buffer[4096];

	for (size_t iter = 0; iter < 1000; iter++) {
		linear = uint32_t{ dis1(engine) };
		nonlinear = uint32_t{ dis1(engine) };
		//filter = uint32_t{ dis1(engine) };

		for (size_t i = 0; i < (655360 / 4096); i++) {
			for (size_t k = 0; k < 4096; k++) {
				unsigned char result = 0;
				int pos = 0;
				for (size_t j = 0; j < 8; j++) {
					pos = (filter & 1 << 7) | (filter&(1 << 8) >> 2) | (filter&(1 << 9) >> 4) | (filter&(1 << 16) >> 12) |
						(filter&(1 << 17) >> 14) | (filter&(1 << 24) >> 22) | (filter&(1 << 27) >> 26) | (filter&(1 << 28) >> 28);
					result <<= 1;
					result |= (values[pos]);// ^ nonlinear ^ ) >> 31;
					nonlinear = (non_lin(nonlinear) & 1) | (nonlinear << 1);
					filter = ((filter >> 1) ^ (filter >> 6) ^ (filter >> 15) ^ (filter >> 31)) & 1 | (filter << 1);
					linear = (linear ^ (linear >> 2) ^ (linear >> 11) ^ (linear >> 16) ^ (linear >> 29) ^ (linear >> 31)) & 1 | (linear << 1);
				}
				//buffer[k] = result;
				fputc(result, stdout);
			}			
			//fwrite(buffer, 1, 4096, stdout);
		}

	}


	return 0;
}