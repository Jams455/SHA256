#include "sha256.h"

#include <array>
#include <string>
#include <cstdint>

#include <iostream>
#include <bitset>

int main()
{
	// Hashing a std::string
	std::cout << "str: ";
	std::string input1{ "abcd" };

	const uint8_t* input1Ptr = reinterpret_cast<const uint8_t*>(input1.data());
	const uint64_t input1Size = input1.size();

	std::array<uint8_t, 32> sha256Hash1 = SHA256::sha256(input1Ptr, input1Size);
	SHA256::OutputHash(sha256Hash1);



	// Hashing a byte array
	std::cout << "bar: ";
	std::array<uint8_t, 4> input2 = { 0x61, 0x62, 0x63, 0x64 };

	const uint8_t* input2Ptr = reinterpret_cast<const uint8_t*>(input2.data());
	const uint64_t input2Size = input2.size();

	std::array<uint8_t, 32> sha256Hash2 = SHA256::sha256(input2Ptr, input2Size);
	SHA256::OutputHash(sha256Hash2);



	// Hashing a byte (uint8_t)
	std::cout << "bte: ";
	const uint8_t input3 { 0xFF };

	const uint8_t* input3Ptr = reinterpret_cast<const uint8_t*>(&input3);
	const uint64_t input3Size = sizeof(input3);

	std::array<uint8_t, 32> sha256Hash3 = SHA256::sha256(input3Ptr, input3Size);
	SHA256::OutputHash(sha256Hash3);



	// Hashing an unsigned integer (uintX_t)
	std::cout << "uin: ";
	const uint32_t input4_LE { 0x61626364 };

	const uint32_t input4_BE = SHA256::SwapEndian32(input4_LE);

	const uint8_t* input4Ptr_BE = reinterpret_cast<const uint8_t*>(&input4_BE);
	const uint64_t input4Size_BE = sizeof(input4_BE);

	std::array<uint8_t, 32> sha256Hash4 = SHA256::sha256(input4Ptr_BE, input4Size_BE);
	SHA256::OutputHash(sha256Hash4);



	// Hashing a signed integer (intX_t)
	std::cout << "int: ";
	const int32_t input5_LE { -0x9E9D9C9C };

	const uint32_t uinput5_LE = static_cast<const uint32_t>(input5_LE);
	const uint32_t uinput5_BE = SHA256::SwapEndian32(uinput5_LE);

	const uint8_t* uinput5Ptr_BE = reinterpret_cast<const uint8_t*>(&uinput5_BE);
	const uint64_t uinput5Size_BE = sizeof(uinput5_BE);

	std::array<uint8_t, 32> sha256Hash5 = SHA256::sha256(uinput5Ptr_BE, uinput5Size_BE);
	SHA256::OutputHash(sha256Hash5);



	// Hashing a hash
	std::cout << "hsh: ";

	const uint8_t* input6Ptr = reinterpret_cast<const uint8_t*>(sha256Hash1.data());
	const uint64_t input6Size = sha256Hash1.size();

	std::array<uint8_t, 32> sha256Hash6 = SHA256::sha256(input6Ptr, input6Size);
	SHA256::OutputHash(sha256Hash6);
}
