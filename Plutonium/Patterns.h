#pragma once

#include "Memory.h"

namespace Patterns
{
	namespace Athena // Chapter 1
	{
		namespace UE_416 // Season 1
		{
			const char* World = "48 8B 1D ? ? ? ? ? ? ? 10 4C 8D 4D ? 4C";
			const char* StaticLoadObject = "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 8B 85 ? ? ? ? 33 F6 4C 8B BD ? ? ? ? 49 8B F9";
			const char* FNameToString = "48 89 5C 24 ? 57 48 83 EC 40 83 79 04 00 48 8B DA 48 8B F9";
			const char* GObjects = "48 8D 0D ? ? ? ? E8 ? ? ? ? E8 ? ? ? ? E8 ? ? ? ? 48 8B D6";
			const char* SpawnActor = "40 53 56 57 48 83 EC 70 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 0F 28 1D ? ? ? ? 0F 57 D2 48 8B B4 24 ? ? ? ? 0F 28 CB";
			const char* GetFullName = "40 53 48 83 EC 20 48 8B C2 48 8B D9 48 85 D2 75 2E";
			const char* FreeMemory = "48 85 C9 74 2E 53 48 83 EC 20 48 8B D9 48 8B 0D ? ? ? ? 48 85 C9 75 0C";
			const char* ProcessEvent = "40 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 48 8D 6C 24 ? 48 89 9D ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C5 48 89 85 ? ? ? ? 48 63 41 0C";
		}
	}

	namespace Artemis // Chapter 3
	{
		namespace UE5 // Season 1
		{
			const char* World = "48 89 05 ? ? ? ? 48 8B 4B 78";
			const char* FNameToString = "48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 56 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 48 8B F2 4C 8B F1 E8 ? ? ? ? 45 8B 06 33 ED";
			const char* FreeMemory = "48 85 C9 0F 84 ? ? ? ? 53 48 83 EC 20 48 89 7C 24 30 48 8B D9 48 8B 3D ? ? ? ? 48 85 FF 0F 84 ? ? ? ? 48 8B 07 4C 8B 40 30 48 8D 05 ? ? ? ? 4C 3B C0";
			const char* GObjects = "48 8B 05 ? ? ? ? 48 8B 0C C8 48 8B 04 D1";
			const char* FortniteCrash = "48 8B C4 48 89 58 08 48 89 70 10 48 89 78 18 4C 89 60 20 55 41 56 41 57 48 8B EC 48 83 EC 40 45 33 FF 4C 8D 35 ? ? ? ?";
			const char* SpawnActor = "48 8B C4 55 53 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 44 0F 29 40 ? 44 0F 29 88 ? ? ? ? 44 0F 29 90 ? ? ? ? 44 0F 29 98 ? ? ? ? 44 0F 29 A0 ? ? ? ? 44 0F 29 A8 ? ? ? ? 44 0F 29 B0 ? ? ? ? 44 0F 29 B8 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 45 33 ED";
			const char* RequestExitWithStatus = "48 8B C4 48 89 58 18 88 50 10 88 48 08 57 48 83 EC 30";
		}
	}
}