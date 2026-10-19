// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Views/View.h"
#include "Views/ViewContent.h"

#include <string>

#include <Memory/UniquePtr.h>

// ------------------------------------------------------------

namespace ost
{
    class ContentView : public View
    {
    public:
        template <typename T>
        static UniquePtr<ContentView> Make()
        {
            return Ptr::NewUnique<ContentView>(Ptr::NewUnique<T>());
        }

        ContentView() = default;
        ContentView(UniquePtr<ViewContent>&& content);

        virtual ~ContentView() = default;
        void Present(const ViewRect& viewRect) override;

    private:
        UniquePtr<ViewContent> _content;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------