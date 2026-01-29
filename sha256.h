#pragma once
#include <array>
#include <cstdint>

namespace SHA256
{
	constexpr uint16_t SwapEndian16(const uint16_t input) noexcept
	{
		return 	((input << 8) 	& 0xFF00) | 
				((input >> 8) 	& 0x00FF) ;
	}

	constexpr uint32_t SwapEndian32(const uint32_t input) noexcept
	{
		return 	((input << 24) 	& 0xFF000000) | 
				((input << 8) 	& 0x00FF0000) | 
				((input >> 8) 	& 0x0000FF00) | 
				((input >> 24) 	& 0x000000FF) ;
	}

	constexpr uint64_t SwapEndian64(const uint64_t input) noexcept
	{
		return 	((input << 56) 	& 0xFF00000000000000) | 
				((input << 40) 	& 0x00FF000000000000) | 
				((input << 24) 	& 0x0000FF0000000000) | 
				((input << 8) 	& 0x000000FF00000000) | 
				((input >> 8) 	& 0x00000000FF000000) | 
				((input >> 24) 	& 0x0000000000FF0000) | 
				((input >> 40) 	& 0x000000000000FF00) | 
				((input >> 56) 	& 0x00000000000000FF) ;
	}

	std::array<uint8_t, 32> sha256(const uint8_t* inputPtr, const uint64_t inputSize);

	void OutputHash(const std::array<uint8_t, 32>& hashBytes) noexcept;
}
