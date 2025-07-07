// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/BasicTypes.h>
#include <OstEngine/Utility/StringHashing.h>
#include <concepts>

#define GEN_TYPE_HASH( str ) ost::string_hash::HashString_64(str)

#define OST_MANAGED_TYPE public: ost::Internal_ManagedObjectData& Internal_GetMOD(){ return _itrl_mod; } private: ost::Internal_ManagedObjectData _itrl_mod;

namespace ost
{
	namespace managed_type_constants
	{
		constexpr uint32 STABLE_IDX_INVALID = 0xFFFFFFFFu;
		constexpr uint32 TYPE_ID_INVALID = 0xFFFFFFFFu;
	}

	struct Internal_ManagedObjectData
	{
	public:
		uint64 GetTypeID() const { return _typeID; }
		uint32 GetStableIndex() const { return _stableIndex; }
		uint32 GetRefCount() const { return _refCount; }
	private:
		friend class Internal_MODHandler;
		uint64 _typeID{0};
		uint32 _stableIndex{0};
		uint32 _refCount{0};
	};

	struct Internal_MODHandler
	{
		static void AssignTypeID(Internal_ManagedObjectData& mod, uint64 tID)
		{
			mod._typeID = tID;
		}

		static void AssignStableID(Internal_ManagedObjectData& mod, uint32 sID)
		{
			mod._stableIndex = sID;
		}

		static void RefIncr(Internal_ManagedObjectData& mod)
		{
			mod._refCount++;
		}

		static void RefDecr(Internal_ManagedObjectData& mod)
		{
			mod._refCount--;
		}
	};

	template<typename T> concept TOstManagedType = requires(T t)
	{
		{ t.Internal_GetMOD() } -> std::same_as<Internal_ManagedObjectData&>;
	};
}

