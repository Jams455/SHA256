#include <iostream>
#include <vector>
#include <string>

#include <cassert> // for assert
#include <cstdint> // for std::int64_t

#include <cstdint>
#include <bitset>

inline uint32_t shr(uint32_t a, uint8_t n)
{
	n %= 32;
	return a >> n;
}

inline uint32_t rotr(uint32_t a, uint8_t n)
{
	n %= 32;
	return (a >> n) | (a << (32 - n));
}

uint32_t s0(uint32_t a)
{
	uint32_t rotr7 = rotr(a, 7);
	uint32_t rotr18 = rotr(a, 18);
	uint32_t shr3 = shr(a, 3);

	return rotr7 ^ rotr18 ^ shr3;
}

uint32_t s1(uint32_t a)
{
	uint32_t rotr17 = rotr(a, 17);
	uint32_t rotr19 = rotr(a, 19);
	uint32_t shr10 = shr(a, 10);

	return rotr17 ^ rotr19 ^ shr10;
}

uint32_t S0(uint32_t a)
{
	uint32_t rotr2 = rotr(a, 2);
	uint32_t rotr13 = rotr(a, 13);
	uint32_t rotr22 = rotr(a, 22);

	return rotr2 ^ rotr13 ^ rotr22;
}

uint32_t S1(uint32_t a)
{
	uint32_t rotr6 = rotr(a, 6);
	uint32_t rotr11 = rotr(a, 11);
	uint32_t rotr25 = rotr(a, 25);

	return rotr6 ^ rotr11 ^ rotr25;
}

inline uint32_t Ch(uint32_t a, uint32_t b, uint32_t c)
{
	return (a & b) | (~a & c);
}

inline uint32_t Maj(uint32_t a, uint32_t b, uint32_t c)
{
	return (a & b) | (a & c) | (b & c);
}

constexpr std::array<uint32_t, 64> K {{
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
}};


int main()
{
	// std::cout << std::bitset<32>(Maj(a, b, c)) << '\n';

	std::vector<char> input { 'a', 'b', 'c' };

	uint64_t inputLength = input.size() * 8;

	uint64_t blockCount = (inputLength + 1 + 64) % 512 + 1;

	for (int i = 0; i < blockCount; ++i)
	{
		
	}






	std::cout << char(98) << '\n';
	std::cout << (uint32_t)(' ') << '\n';

	std::vector<char> input { 'a', 'b', 'c' };
	uint64_t inputLength = input.size();
	input.push_back(0b10000000);

	while ((input.size() / 4 + 2) % 16 != 0)
	{
		input.push_back(0x00);
	}



	std::vector<std::array<uint8_t, 4>> messageSchedule;

	for (int i = 0; i*8 < ; i++)
	{
		messageSchedule[i / 4][i % 4] = int(input[i]);
	}

}

(512*n - 64)
