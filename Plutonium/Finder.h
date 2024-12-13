#pragma once

#include "SDK.h"

namespace Finder
{
	using namespace SDK;

	int GetOffset(void* TargetProp)
	{
		if (FortniteVersion < 12.0) {
			return *reinterpret_cast<int*>(__int64(TargetProp) + 0x44);
		}
		else
		{
			return *reinterpret_cast<int*>(__int64(TargetProp) + 0x4C);
		}
	}

	template<class T>
	T GetValuePointer(UObject* Object, void* Prop)
	{
		return reinterpret_cast<T>(Object->GetAddress() + GetOffset(Prop));
	}
}