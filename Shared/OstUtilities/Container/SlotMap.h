// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Container/List.h"
#include "Container/Queue.h"
#include "Container/SparseList.h"

// ------------------------------------------------------------

namespace ost
{

    template <typename T>
    class SlotMap
    {
    public:
        SlotMap() = default;
        SlotMap(const SlotMap&) = default;
        SlotMap(SlotMap&&) noexcept = default;
        ~SlotMap() = default;

        SlotMap& operator=(const SlotMap&) = default;
        SlotMap& operator=(SlotMap&&) noexcept = default;

        Uint64 Add(const T& t)
        {
            const SizeType slotIndex = GetNextSlotIndex();
            Slot& slot = _slots[slotIndex];
            slot.denseIndex = _denseList.GetSize();
            slot.generation++;
            _denseList.Add(t);
            _denseToSlotIndex.Add(slotIndex);

            const SlotHandle slotHandle{slot.generation, slotIndex};
            return slotHandle.PackToInt();
        }
        Uint64 Add(T&& t)
        {
            const SizeType slotIndex = GetNextSlotIndex();
            Slot& slot = _slots[slotIndex];
            slot.denseIndex = _denseList.GetSize();
            slot.generation++;
            _denseList.Add(std::move(t));
            _denseToSlotIndex.Add(slotIndex);

            const SlotHandle slotHandle{slot.generation, slotIndex};
            return slotHandle.PackToInt();
        }

        void Remove(Uint64 handle)
        {
            const SlotHandle removedSlotHandle = SlotHandle::UnpackFromInt(handle);
            Slot& removedSlot = _slots[removedSlotHandle.slotIndex];

            OST_ASSERT(removedSlot.generation == removedSlotHandle.generation, "Generation must match");

            // Removing from the dense list is a swap and pop action
            // So if the removed dense element wasn't at the end of our dense list, we'll have to also reassign the dense index mapping for the slot
            // that was referencing the last element before the removal
            const bool updateSwappedElement = removedSlot.denseIndex < (_denseList.GetSize() - 1);
            if (updateSwappedElement)
            {
                const SizeType swappedSlotIndex = _denseToSlotIndex[_denseList.GetSize() - 1];
                _slots[swappedSlotIndex].denseIndex = removedSlot.denseIndex;
            }

            // Now we can actually remove the element (we've repointed the swapped slot if necessary)
            _denseList.Remove(removedSlot.denseIndex);
            _denseToSlotIndex.Remove(removedSlot.denseIndex);

            // Now unpoint the dense index, up the generation (to invalidate stale stable indexes) and push to our slot indexes for recycling
            removedSlot.generation++;
            removedSlot.denseIndex = 0;
            _freeSlots.Push(removedSlotHandle.slotIndex);
        }

        T& operator[](Uint64 handle)
        {
            const auto slotHandle = SlotHandle::UnpackFromInt(handle);
            const Slot& slot = _slots[slotHandle.slotIndex];

            OST_ASSERT(slot.generation == slotHandle.generation, "Generation must match");

            return _denseList[slot.denseIndex];
        }
        const T& operator[](Uint64 handle) const
        {
            const auto slotHandle = SlotHandle::UnpackFromInt(handle);
            const Slot& slot = _slots[slotHandle.slotIndex];

            OST_ASSERT(slot.generation == slotHandle.generation, "Generation must match");

            return _denseList[slot.denseIndex];
        }

        const List<T>& GetDenseList() const
        {
            return _denseList;
        }

    private:
        struct Slot
        {
            Uint64 generation = 0;
            Uint64 denseIndex = 0;
        };
        struct SlotHandle
        {
            constexpr static Uint64 GENERATION_MASK = 0x000000000000FFFFu;
            constexpr static Uint64 INDEX_MASK = 0xFFFFFFFFFFFF0000u;

            Uint64 generation = 0;
            Uint64 slotIndex = 0;

            static SlotHandle UnpackFromInt(Uint64 h)
            {
                return {h & GENERATION_MASK, (h & INDEX_MASK) >> 16};
            }

            Uint64 PackToInt() const
            {

                return (generation & GENERATION_MASK) | (slotIndex << 16);
            }
        };

        SizeType GetNextSlotIndex()
        {
            if (_freeSlots.IsEmpty())
            {
                _slots.Emplace();
                return _slots.GetSize() - 1;
            }
            else
            {
                return _freeSlots.Pop();
            }
        }

    private:
        List<Slot> _slots;
        Queue<SizeType> _freeSlots;

        List<T> _denseList;
        List<SizeType> _denseToSlotIndex;
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------