// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/ObjectSystem/ManagedType/ManagedObjectType.h>
#include <OstEngine/ObjectSystem/ManagedType/StableIdxLookup.h>

#include <vector>
#include <utility>

// ------------------------------------------------------------

namespace ost
{
	class CGameObject;
	class CComponent;

	// ------------------------------------------------------------
	// Base class for all managed type containers
	// ------------------------------------------------------------
	class CManagedTypeContainerBase
	{
	public:
		virtual ~CManagedTypeContainerBase() = default;

		virtual uint64 GetContainerStorageTypeID() const = 0;

		virtual Internal_ManagedObjectData& GetManagedObjectData(uint32 stableIdx) = 0;
		virtual void* GetRawObjectPtr(uint32 stableIdx) = 0;
		virtual const void* GetRawObjectPtr(uint32 stableIdx) const = 0;
	private:
		CStableIdxLookup _stableLookup;

	protected:
		template<TOstManagedType T>
		T& GetFunc(std::vector<T>& denseList, uint32 stableIdx)
		{
			return denseList[_stableLookup.StableToDenseIdx(stableIdx)];
		}

		template<TOstManagedType T>
		const T& GetFunc(const std::vector<T>& denseList, uint32 stableIdx) const
		{
			return denseList[_stableLookup.StableToDenseIdx(stableIdx)];
		}

		template<TOstManagedType T, typename ... TArgs>
		uint32 EmplaceFunc(std::vector<T>& denseList, uint64 typeUID, TArgs&& ... args)
		{
			// Generate the dense and stable indexes
			const uint32 createdObjDenseIdx = static_cast<uint32>(denseList.size());
			const uint32 createdObjStableIdx = _stableLookup.GenerateStableIDX();

			// Map the stable index to the dense index
			_stableLookup.MapStableToDenseIdx(createdObjStableIdx, createdObjDenseIdx);

			T& created = denseList.emplace_back(args...);

			// Assign the created object's stable index and type id
			Internal_MODHandler::AssignStableID(created.Internal_GetMOD(), createdObjStableIdx);
			Internal_MODHandler::AssignTypeID(created.Internal_GetMOD(), typeUID);

			return createdObjStableIdx;
		}

		template<TOstManagedType T>
		Internal_ManagedObjectData& GetManagedObjectDataFunc(std::vector<T>& denseList, uint32 stableIdx)
		{
			return denseList[_stableLookup.StableToDenseIdx(stableIdx)].Internal_GetMOD();
		}

		template<TOstManagedType T>
		void RemoveFunc(std::vector<T>& denseList, uint32 removeStableIndex)
		{
			const uint32 movedStableIndex = denseList.back().Internal_GetMOD().GetStableIndex();
			const uint32 removedDenseIndex = _stableLookup.StableToDenseIdx(removeStableIndex);

			// Swap location of the last element and the to-be removed
			// This allows us to pop back for O(1) removal
			std::swap(denseList.back(), denseList[removedDenseIndex]);

			// Update the mapping of the moved and kept elements stable -> dense
			_stableLookup.MapStableToDenseIdx(movedStableIndex, removedDenseIndex);

			// Pop the last element and recycle the removed stable index
			denseList.pop_back();
			_stableLookup.RecycleStableIDX(removeStableIndex);
		}
	};

	// ------------------------------------------------------------
	// Extended base class for component type container
	// ------------------------------------------------------------
	class CManagedTypeContainerBase_Component : public CManagedTypeContainerBase
	{
	public:
		virtual ~CManagedTypeContainerBase_Component() = default;

		virtual CComponent& NewComponent() = 0;

		virtual void TickAll() = 0;

		virtual CComponent& GetBase(uint32 stableIdx) = 0;
		virtual const CComponent& GetBase(uint32 stableIdx) const = 0;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------