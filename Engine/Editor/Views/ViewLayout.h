// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Views/View.h"

#include <Container/List.h>
#include <Math/Vector2.h>
#include <Memory/UniquePtr.h>
#include <Utility/Assert.h>
// ------------------------------------------------------------

namespace ost
{
    enum class ELayoutDirection
    {
        Horizontal,
        Vertical,
    };

    class ViewLayout : public View
    {
    public:
        ViewLayout& SetDirection(ELayoutDirection direction);
        ViewLayout& SetViewSlotCount(Uint32 numViewSlots);
        ViewLayout& SetViewSlotSize(Uint32 viewSlotIndex, Float32 size);
        ViewLayout& SetViewSlotContent(Uint32 viewSlotIndex, UniquePtr<View>&& content);
        void Finalize();

        void Present(const ViewRect& viewRect, PropertyEditorCollection& propertyEditor) override;

    private:
        struct ViewSlot
        {
            Float32 divideFraction;
            UniquePtr<View> view;
        };

        ELayoutDirection _direction;
        List<ViewSlot> _viewSlots;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------