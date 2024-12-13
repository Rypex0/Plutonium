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

	void(*FNameToString)(FName* In, class FString& Out);
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

	void*(*ProcessEventOG)(void* Object, void* Function, void* Params);

	struct UObject
	{
		void** VTable;
		int32_t ObjectFlags;
		int32_t InternalIndex;
		UObject* Class;
		FName Name;
		UObject* Outer;

		uintptr_t GetAddress()
		{
			return __int64(this);
		}

		bool IsA(UObject* CMP) const
		{
			if (CMP == Class)
				return false;
			return false;
		}

		void* ProcessEvent(UObject* Function, void* Params = nullptr)
		{
			return ProcessEventOG(this, Function, Params);
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

	struct FGuid
	{
		int A;
		int B;
		int C;
		int D;
	};

	struct UObjectItem
	{
		UObject* Object;
		DWORD Flags;
		DWORD ClusterIndex;
		DWORD SerialNumber;
	};

	struct PreUObjectItem
	{
		UObjectItem* FUObject[10];
	};

	class NewUObjectArray
	{
	public:
		UObjectItem* Objects[9];
	};

	struct GObjects
	{
		NewUObjectArray* ObjectArray;
		BYTE _padding_0[0xC];
		uint32_t NumElements;

		inline void NumChunks(int* Start, int* End) const
		{
			int cStart = 0, cEnd = 0;

			if (!cEnd)
			{
				while (1)
				{
					if (ObjectArray->Objects[cStart] == 0)
					{
						cStart++;
					}
					else
					{
						break;
					}
				}

				cEnd = cStart;
				while (1)
				{
					if (ObjectArray->Objects[cEnd] == 0)
					{
						break;
					}
					else
					{
						cEnd++;
					}
				}
			}

			*Start = cStart;
			*End = cEnd;
		}

		inline int32_t Num() const
		{
			return NumElements;
		}

		inline UObject* GetByIndex(int32_t Index) const
		{
			int cStart = 0, cEnd = 0;
			int ChunkIndex = 0, ChunkSize = 0xFFFF, ChunkPosition;
			UObjectItem* Object;

			NumChunks(&cStart, &cEnd);

			ChunkIndex = Index / ChunkSize;
			if (ChunkSize * ChunkIndex != 0 && ChunkSize * ChunkIndex == Index)
			{
				ChunkIndex--;
			}

			ChunkPosition = cStart + ChunkIndex;
			if (ChunkPosition < cEnd)
			{
				Object = ObjectArray->Objects[ChunkPosition] + (Index - ChunkSize * ChunkIndex);
				return Object->Object;
			}

			return nullptr;
		}
	};

	class UObjectArray
	{
	public:
		inline int Num() const
		{
			return NumElements;
		}

		inline UObject* GetByIndex(int32_t Index) const
		{
			return (&Objects[Index])->Object;
		}
	private:
		UObjectItem* Objects;
		int MaxElements;
		int NumElements;
	};

	struct FVector
	{
		float X;
		float Y;
		float Z;

		FVector()
		{
			X = Y = Z = 0;
		}

		FVector(float PX, float PY, float PZ)
		{
			X = PX;
			Y = PY;
			Z = PZ;
		}
	};

	template <class TEnum>
	class TEnumAsByte
	{
	public:
		TEnumAsByte() {}

		TEnumAsByte(TEnum value) : Value(static_cast<uint8_t>(value)) {}

		explicit TEnumAsByte(int32_t value) : Value(static_cast<uint8_t>(value)) {}

		explicit TEnumAsByte(uint8_t value) : Value(value) {}

		operator TEnum() const
		{
			return static_cast<TEnum>(Value);
		}

		TEnum GetValue() const
		{
			return static_cast<TEnum>(Value);
		}

	private:
		uint8_t Value;
	};

	namespace Pointer
	{
		SDK::UObject* Value;
	}

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

	struct FActorSpawnParameters
	{
		SDK::FName Name;

		SDK::UObject* Template;

		SDK::UObject* Owner;

		SDK::UObject* Instigator;

		SDK::UObject* OverrideLevel;

		ESpawnActorCollisionHandlingMethod SpawnCollisionHandlingOverride;

		FActorSpawnParameters() : Name(), Template(nullptr), Owner(nullptr), Instigator(nullptr), OverrideLevel(nullptr), SpawnCollisionHandlingOverride(), bRemoteOwned(0), bNoFail(0), bDeferConstruction(0), bAllowDuringConstructionScript(0), NameMode(), ObjectFlags() {};

	private:
		uint8_t bRemoteOwned : 1;

	public:

		bool IsRemoteOwned() const { return bRemoteOwned; }

		uint8_t bNoFail : 1;

		uint8_t bDeferConstruction : 1;

		uint8_t bAllowDuringConstructionScript : 1;

		enum class ESpawnActorNameMode : uint8_t
		{
			Required_Fatal,
			Required_ErrorAndReturnNull,
			Required_ReturnNull,
			Requested
		};

		ESpawnActorNameMode NameMode;

		uint8_t ObjectFlags;
	};

	struct UField_Old : UObject
	{
		UField_Old* Next;
	};

	struct UField_New : UObject
	{
		UField_New* Next;
		void* UKD_0;
		void* UKD_1;
	};

	struct UStruct_Old : UField_Old
	{
		UStruct_Old* Super;
		UField_Old* Children;
		uint32_t Size;
		char PAD[0x44];
	};

	struct UStruct_New : UField_New
	{
		UStruct_New* Super;
		UField_New* Children;
		uint32_t Size;
		char PAD[0x44];
	};

	struct FField
	{
		void* VTable;
		void* Class;
		void* Owner;
		void* UKD_00;
		FField* Next;
		FName Name;
		int32_t FlagsPrivate;
	};

	struct FProperty : FField
	{
		int32_t ArrayDim;
		int32_t ElementSize;
		int32_t PropertyFlags;
		int32_t RepIndex;
		void* BlueprintReplicationCondition;
		int32_t Offset_Internal;
		FName RepNotifyFunc;
		FProperty* PropertyLinkNext;
		FProperty* NextRef;
		FProperty* DestructorLinkNext;
		FProperty* PostConstructLinkNext;
	};

	struct UStruct_New2 : UField_New
	{
		UStruct_New2* Super;
		UField_New* Children;
		FField* ChildProperties;
		int32_t Size;
		int32_t MinAlignment;
		TArray<uint8_t> Script;
		FProperty* PropertyLink;
		FProperty* RefLink;
		FProperty* DestructorLink;
		FProperty* PostConstructLink;
	};

	SDK::UObject*(*GetFirstPlayerController)(SDK::UObject* World);
	SDK::UObject*(*StaticLoadObjectInternal)(SDK::UObject*, SDK::UObject*, const TCHAR*, const TCHAR*, uint32_t, SDK::UObject*, bool);
	SDK::UObject*(*StaticConstructObjectInternal)(void*, void*, void*, int, unsigned int, void*, bool, void*, bool);
	SDK::UObject*(*SpawnActor)(SDK::UObject* World, SDK::UObject* Class, SDK::FVector* Location, SDK::FVector* Rotation, const FActorSpawnParameters& SpawnParameters);
}

namespace Core {}