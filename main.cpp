#include <iostream>
#include <iomanip>
#include <vector>
#include <array>
#include <string>

#include <cassert> // for assert

#include <cstdint>
#include <bitset>

namespace SHA256
{
	constexpr uint32_t shr(uint32_t a, uint8_t n) noexcept
	{
		return a >> n;
	}

	constexpr uint32_t rotr(uint32_t a, uint8_t n) noexcept
	{
		return (a >> n) | (a << (32 - n));
	}

	constexpr uint32_t s0(uint32_t a) noexcept
	{
		uint32_t rotr7 = rotr(a, 7);
		uint32_t rotr18 = rotr(a, 18);
		uint32_t shr3 = shr(a, 3);

		return rotr7 ^ rotr18 ^ shr3;
	}

	constexpr uint32_t s1(uint32_t a) noexcept
	{
		uint32_t rotr17 = rotr(a, 17);
		uint32_t rotr19 = rotr(a, 19);
		uint32_t shr10 = shr(a, 10);

		return rotr17 ^ rotr19 ^ shr10;
	}

	constexpr uint32_t S0(uint32_t a) noexcept
	{
		uint32_t rotr2 = rotr(a, 2);
		uint32_t rotr13 = rotr(a, 13);
		uint32_t rotr22 = rotr(a, 22);

		return rotr2 ^ rotr13 ^ rotr22;
	}

	constexpr uint32_t S1(uint32_t a) noexcept
	{
		uint32_t rotr6 = rotr(a, 6);
		uint32_t rotr11 = rotr(a, 11);
		uint32_t rotr25 = rotr(a, 25);

		return rotr6 ^ rotr11 ^ rotr25;
	}

	constexpr uint32_t Ch(uint32_t a, uint32_t b, uint32_t c) noexcept
	{
		return (a & b) | (~a & c);
	}

	constexpr uint32_t Maj(uint32_t a, uint32_t b, uint32_t c) noexcept
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

	constexpr std::array<uint32_t, 8> H {{
		0x6a09e667,
		0xbb67ae85,
		0x3c6ef372,
		0xa54ff53a,
		0x510e527f,
		0x9b05688c,
		0x1f83d9ab,
		0x5be0cd19
	}};

	void PadMsgSchedule(std::array<uint32_t, 64>& W)
	{
		for (size_t i = 16; i < 64; ++i)
		{
			W[i] = s1(W[i-2]) + W[i-7] + s0(W[i-15]) + W[i-16];
		}
	}

	std::array<uint32_t, 64> GenMsgSchedule(const std::string& totalInput, uint64_t blockIndex, uint64_t blockCount)
	{
		uint64_t rawInputByteCount = totalInput.size();
		uint64_t currPos = blockIndex * 64;

		uint64_t blockInputLength {};

		if 		(rawInputByteCount > currPos + 64) 	{ blockInputLength = 64; }
		else if (rawInputByteCount > currPos)		{ blockInputLength = rawInputByteCount - currPos; }
		else										{ blockInputLength = 0; }

		std::string input;
		if (blockInputLength > 0) { input = totalInput.substr(currPos, blockInputLength); }

		std::array<uint32_t, 64> W {};

		for (uint32_t charID = 0; charID < blockInputLength; ++charID)
		{
			uint32_t wordID = charID / 4;
			uint32_t charShift = (3 - (charID % 4 )) * 8;
			uint32_t currChar = static_cast<uint8_t>(input[charID]);
			W[wordID] |= currChar << charShift;
		}

		if (blockIndex == blockCount - 1)
		{
			uint64_t totalInputSizeInBits = (totalInput.size() - 1) * 8;
			W[14] = totalInputSizeInBits >> 32;
			W[15] = totalInputSizeInBits;
		}

		PadMsgSchedule(W);

		return W;
	}

	std::array<uint32_t, 8> Compression(const std::array<uint32_t, 64>& W, 
										const std::array<uint32_t, 64>& K, 
										const std::array<uint32_t, 8>& H)
	{
		uint32_t a = H[0], 
				b = H[1], 
				c = H[2], 
				d = H[3], 
				e = H[4], 
				f = H[5], 
				g = H[6], 
				h = H[7];

		for (size_t i = 0; i < 64; ++i)
		{
			uint32_t T1 = S1(e)
					+ Ch(e, f, g)
					+ h
					+ K[i]
					+ W[i];
		
			uint32_t T2 = S0(a)
					+ Maj(a, b, c);
			
			h = g;
			g = f;
			f = e;
			e = d + T1;
			d = c;
			c = b;
			b = a;
			a = T1 + T2;
		}

		return {a + H[0],
				b + H[1],
				c + H[2],
				d + H[3],
				e + H[4],
				f + H[5],
				g + H[6],
				h + H[7]};
	}

	std::array<uint8_t, 32> ToBytes(const std::array<uint32_t, 8>& hashWords)
	{
		std::array<uint8_t, 32> hashBytes {};

		for (size_t i = 0; i < 32; ++i)
		{
			hashBytes[i] = static_cast<uint8_t>((hashWords[i/4] >> (3 - (i%4)) * 8) & 0xFF);
		}

		return hashBytes;
	}

	std::array<uint8_t, 32> sha256(const std::string& input)
	{
		uint64_t rawInputByteCount = input.size();
		uint64_t totalByteCount = (rawInputByteCount + 8);
		uint64_t paddedByteCount = ((totalByteCount + 63) / 64) * 64;
		uint64_t blockCount = paddedByteCount / 64;
		
		std::array<uint32_t, 8> registers = H;

		for (uint64_t blockID = 0; blockID < blockCount; ++blockID)
		{	
			std::array<uint32_t, 64> W = GenMsgSchedule(input, blockID, blockCount);

			registers = Compression(W, K, registers);
		}

		std::array<uint8_t, 32> hashBytes = ToBytes(registers);

		return hashBytes;
	}

	void OutputHash(const std::array<uint8_t, 32> hashBytes)
	{
		std::cout << std::hex;
		for (size_t i = 0; i < 32; ++i)
		{
			std::cout << std::setw(2)
					<< std::setfill('0')
					<< static_cast<int>(hashBytes[i]);
		}
		std::cout << std::dec << '\n';
	}
}

int main()
{
	std::string input = { "aaaaabbbbbcccccdddddeeeeefffffggggghhhhhiiiiijjjjjkkkkk" };
	
	input.push_back(0x80);

	std::array<uint8_t, 32> sha256Hash = SHA256::sha256(input);

	SHA256::OutputHash(sha256Hash);
}

//abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyabcdefgfuinq12wunfioqwenfioqweunfqiwouenfqoiwuenfiqwuenfqiwoeufnqiwuenfqiweu34niqewuofn
