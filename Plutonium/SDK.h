#pragma once

#include <locale>
#include <ostream>
#include <fstream>
#include <sstream>

#include "Memory.h"

inline double FortniteVersion = 0.0;

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

	struct FString : private TArray<wchar_t>
	{
		FString() {};

		FString(const wchar_t* Other)
		{
			Max = Count = *Other ? std::wcslen(Other) + 1 : 0;

			if (Count)
			{
				Data = const_cast<wchar_t*>(Other);
			}
		}

		bool IsValid() const
		{
			return Data != nullptr;
		}

		const wchar_t* c_str() const
		{
			return Data;
		}

		std::string ToString() const
		{
			auto Length = std::wcslen(Data);

			std::string STR(Length, '\0');

			std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Data, Data + Length, '?', &STR[0]);

			return STR;
		}
	};

	struct FName;

	void (*FNameToString)(FName* In, class FString& Out);
	void(*FreeMemory)(__int64);

	struct FName
	{
		uint32_t ComparisonIndex;
		uint32_t DisplayIndex;

		FName() = default;

		std::string ToString()
		{
			FString Temp;
			FNameToString(this, Temp);
			std::string Ret(Temp.ToString());
			FreeMemory(__int64(Temp.c_str()));

			return Ret;
		}
	};

	struct UObject;

	FString(*GetObjectFullName)(UObject* In);

	struct UObject
	{
		void** VTable;
		int32_t ObjectFlags;
		int32_t InternalIndex;
		UObject* Class;
		FName Name;
		UObject* Outer;

		bool IsA(UObject* CMP) const
		{
			if (CMP == Class)
				return false;
			return false;
		}

		/*std::string GetName()
		{
			return GetObjectFullName(this).ToString();
		}*/

		std::string GetName()
		{
			return Name.ToString();
		}

		std::string GetFullName()
		{
			std::string Temp;

			for (auto outer = Outer; outer; outer = outer->Outer)
			{
				Temp = outer->Name.ToString() + "." + Temp;
			}

			Temp = reinterpret_cast<UObject*>(Class)->Name.ToString() + " " + Temp + this->Name.ToString();

			return Temp;
		}
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