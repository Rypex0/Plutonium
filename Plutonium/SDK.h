#pragma once

#include <locale>
#include <ostream>
#include <fstream>
#include <sstream>

#include "Memory.h"

namespace SDK
{
	template <class T>
	struct TArray
	{
		friend class FString;

	public:
		inline TArray()
		{
			Data = nullptr;
			Count = Max = 0;
		}

		inline int Num() const
		{
			return Count;
		}

		inline void Add(T InputData)
		{
			Data = (T*)realloc(Data, sizeof(T) * (Count + 1));
			Data[Count++] = InputData;
			Max = Count;
		}

		inline void Remove(int32_t Index)
		{
			TArray<T> NewArray;
			for (int i = 0; i < this->Count; i++)
			{
				if (i == Index)
					continue;

				NewArray.Add(this->Data[i]);
			}
			this->Data = (T*)realloc(NewArray.Data, sizeof(T) * (NewArray.Count));
			this->Count = NewArray.Count;
			this->Max = NewArray.Count;
		}

		T* Data;
		int Count;
		int Max;
	};

	enum class EFortCustomPartType : uint8_t
	{
		Head = 0,
		Body = 1,
		Hat = 2,
		Backpack = 3,
		Charm = 4,
		Face = 5,
		NumTypes = 6,
		EFortCustomPartType_MAX = 7
	};

	struct BitField
	{
		unsigned char A : 1;
		unsigned char B : 1;
		unsigned char C : 1;
		unsigned char D : 1;
		unsigned char E : 1;
		unsigned char F : 1;
		unsigned char G : 1;
		unsigned char H : 1;
	};

	enum class ESpawnActorCollisionHandlingMethod : uint8_t
	{
		Undefined = 0,
		AlwaysSpawn = 1,
		AdjustIfPossibleButAlwaysSpawn = 2,
		AdjustIfPossibleButDontSpawnIfColliding = 3,
		DontSpawnIfColliding = 4,
		ESpawnActorCollisionHandlingMethod_MAX = 5
	};
}