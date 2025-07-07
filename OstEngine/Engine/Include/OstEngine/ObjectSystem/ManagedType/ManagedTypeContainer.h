// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/ObjectSystem/ManagedType/ManagedTypeContainerBase.h>
#include <OstEngine/ObjectSystem/ManagedType/ManagedObjectPtr.h>
#include <OstEngine/ObjectSystem/Component.h>

namespace ost
{
	// ------------------------------------------------------------
	// Basic managed type container template
	// ------------------------------------------------------------
	template<TOstManagedType T>
	class TManagedTypeContainer final : public CManagedTypeContainerBase
	{
	public:
		template<typename ... TArgs>
		TPtr<T> Emplace(TArgs&&... args)
		{
			const uint32 stableIdx = EmplaceFunc<T>(_denseList, T::StaticUID, args...);
			return TPtr<T>(stableIdx, this);
		}

		void Remove(uint32 stableIdx) { RemoveFunc<T>(_denseList, stableIdx); }

		uint64 GetContainerStorageTypeID() const override { return T::StaticUID; }

		void* GetRawObjectPtr(uint32 stableIdx) override
		{
			return &Get(stableIdx);
		}

		const void* GetRawObjectPtr(uint32 stableIdx) const override
		{
			return &Get(stableIdx);
		}

		T& Get(uint32 stableIdx) { return GetFunc<T>(_denseList, stableIdx); }
		const T& Get(uint32 stableIdx) const { return GetFunc<T>(_denseList, stableIdx); }

		Internal_ManagedObjectData& GetManagedObjectData(uint32 stableIdx) override { return GetManagedObjectDataFunc<T>(_denseList, stableIdx); }

	private:
		std::vector<T> _denseList;
	};

	template<typename T> concept TTickableOstComponentType = TOstComponentType<T> && requires(T & t)
	{
		{ t.Tick() };
	};

	// ------------------------------------------------------------
	// Specialisation TManagedTypeContainer<COMPONENT TYPE>
	// ------------------------------------------------------------
	template<TOstManagedType T> requires TOstComponentType<T>
	class TManagedTypeContainer<T> final : public CManagedTypeContainerBase_Component
	{
	public:
		template<typename ... TArgs>
		TPtr<T> Emplace(TArgs&&... args)
		{
			const uint32 stableIdx = EmplaceFunc<T>(_denseList, T::ReflectionData::TypeUID, args...);
			return TPtr<T>(stableIdx, this);
		}

		uint64 GetContainerStorageTypeID() const override { return T::ReflectionData::TypeUID; }

		void Remove(uint32 stableIdx) { RemoveFunc<T>(_denseList, stableIdx); }

		T& Get(uint32 stableIdx) { return GetFunc<T>(_denseList, stableIdx); }
		const T& Get(uint32 stableIdx) const { return GetFunc<T>(_denseList, stableIdx); }

		CComponent& GetBase(uint32 stableIdx) override { return Get(stableIdx); }
		const CComponent& GetBase(uint32 stableIdx) const override { return Get(stableIdx); }

		Internal_ManagedObjectData& GetManagedObjectData(uint32 stableIdx) override { return GetManagedObjectDataFunc<T>(_denseList, stableIdx); }

		void TickAll() override
		{
			// Optionally invoke tick only on component types that implements a tick function
			if constexpr (TTickableOstComponentType<T>) 
			{
				for (auto& c : _denseList)
				{
					c.Tick();
				}
			}
		}

		CComponent& NewComponent() override
		{
			const uint32 stableIdx = EmplaceFunc<T>(_denseList, T::ReflectionData::TypeUID);
			return GetFunc(_denseList, stableIdx);
		}

		void* GetRawObjectPtr(uint32 stableIdx) override
		{
			return &Get(stableIdx);
		}

		const void* GetRawObjectPtr(uint32 stableIdx) const override
		{
			return &Get(stableIdx);
		}
	private:
		std::vector<T> _denseList;
	};
}