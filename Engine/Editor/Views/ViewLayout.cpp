// Kasper "OstGeneralen" Esbjornsson - 2026
#include "ViewLayout.h"

using namespace ost;

// ------------------------------------------------------------

ViewLayout& ost::ViewLayout::SetDirection(ELayoutDirection direction)
{
    _direction = direction;
    return *this;
}

ViewLayout& ost::ViewLayout::SetViewSlotCount(Uint32 numViewSlots)
{
    _viewSlots = List<ViewSlot>(numViewSlots);
    const Float32 fractionPerSlot = 1.0f / static_cast<Float32>(numViewSlots);

    for (auto& slot : _viewSlots)
    {
        slot.divideFraction = fractionPerSlot;
    }
    return *this;
}

ViewLayout& ost::ViewLayout::SetViewSlotSize(Uint32 viewSlotIndex, Float32 size)
{
    _viewSlots[viewSlotIndex].divideFraction = size;
    return *this;
}

ViewLayout& ost::ViewLayout::SetViewSlotContent(Uint32 viewSlotIndex, UniquePtr<View>&& content)
{
    _viewSlots[viewSlotIndex].view = std::move(content);
    return *this;
}

void ost::ViewLayout::Finalize()
{
    Float32 sizeSum = 0.0f;
    for (const auto& viewSlot : _viewSlots)
    {
        sizeSum += viewSlot.divideFraction;
    }

    for (auto& viewSlot : _viewSlots)
    {
        viewSlot.divideFraction = viewSlot.divideFraction / sizeSum;
    }
}

void ViewLayout::Present(const ViewRect& viewRect, PropertyEditorCollection& propertyEditor)
{
    Float32 positionOffset = 0;

    for (auto& slot : _viewSlots)
    {
        const Float32 size = slot.divideFraction;

        ViewRect subRect;
        subRect.position = viewRect.position;
        subRect.size = viewRect.size;

        switch (_direction)
        {
        case ELayoutDirection::Horizontal: {
            subRect.position.X += positionOffset;
            subRect.size.X = viewRect.size.X * slot.divideFraction;
            positionOffset += subRect.size.X;
            break;
        }
        case ELayoutDirection::Vertical: {
            subRect.position.Y += positionOffset;
            subRect.size.Y = viewRect.size.Y * slot.divideFraction;
            positionOffset += subRect.size.Y;
            break;
        }
        }

        if (slot.view)
        {
            slot.view->Present(subRect, propertyEditor);
        }
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------