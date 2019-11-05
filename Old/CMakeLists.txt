cmake_minimum_required (VERSION 3.1.0)
project (SeqGen)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O2")


add_executable(main LFSR.cpp NFSR.cpp CombFuncReg.cpp FuncReg.cpp MixedFuncReg.cpp main.cpp)

add_executable(xortest LFSR.cpp NFSR.cpp LinearCombXOR.cpp)

add_executable(super LFSR.cpp NFSR.cpp FuncReg.cpp SuperGen.cpp)

add_executable(super_s_block LFSR.cpp NFSR.cpp FuncReg.cpp SuperGen.cpp)
target_compile_definitions(super_s_block PRIVATE S_BLOCK)

add_executable(linearxor LFSR.cpp NFSR.cpp FuncReg.cpp SuperGen.cpp)
target_compile_definitions(linearxor PRIVATE LINEAR_XOR)

add_executable(nonlinear LFSR.cpp NFSR.cpp FuncReg.cpp SuperGen.cpp)
target_compile_definitions(nonlinear PRIVATE NON_LINEAR)