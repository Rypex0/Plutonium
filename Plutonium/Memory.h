#pragma once

#include <Windows.h>
#include <string>
#include <vector>
#include <iostream>

namespace Memory
{
	// Credits: Twin1
	uintptr_t SigScan(const char* Signature, bool bRelative = false, uint32_t Offset = 0)
	{
		uintptr_t BaseAddress = reinterpret_cast<uintptr_t>(GetModuleHandle(NULL));
		static auto PatternToByte = [](const char* Pattern)
			{
				auto Bytes = std::vector<int>{};
				const auto Start = const_cast<char*>(Pattern);
				const auto End = const_cast<char*>(Pattern) + strlen(Pattern);

				for (auto Current = Start; Current < End; ++Current)
				{
					if (*Current == '?')
					{
						++Current;
						if (*Current == '?') ++Current;
						Bytes.push_back(-1);
					}
					else { Bytes.push_back(strtoul(Current, &Current, 16)); }
				}

				return Bytes;
			};

		const auto DosHeader = (PIMAGE_DOS_HEADER)BaseAddress;
		const auto NTHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)BaseAddress + DosHeader->e_lfanew);

		const auto SizeOfImage = NTHeaders->OptionalHeader.SizeOfImage;
		auto PatternBytes = PatternToByte(Signature);
		const auto ScanBytes = reinterpret_cast<std::uint8_t*>(BaseAddress);

		const auto Size = PatternBytes.size();
		const auto Data = PatternBytes.data();

		for (auto i = 0ul; i < SizeOfImage - Size; i++)
		{
			bool Found = true;
			for (auto j = 0ul; j < Size; ++j)
			{
				if (ScanBytes[i + j] != Data[j] && Data[j] != -1)
				{
					Found = false;
					break;
				}
				if (Found)
				{
					uintptr_t Address = reinterpret_cast<uintptr_t>(&ScanBytes[i]);
					if (bRelative)
					{
						Address = ((Address + Offset + 4) + *(int32_t*)(Address + Offset));
						return Address;
					}
					return Address;
				}
			}
		}
		return 0;
	}
}