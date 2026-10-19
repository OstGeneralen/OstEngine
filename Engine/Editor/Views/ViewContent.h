// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Views/View.h"

#include <string>

// ------------------------------------------------------------

namespace ost
{
    class ViewContent
    {
    public:
        ViewContent(const std::string& name)
            : _name{name}
        {
        }
        virtual ~ViewContent() = default;
        virtual void Present(const ViewRect& viewRect) = 0;

        const std::string& GetName() const
        {
            return _name;
        }

    private:
        std::string _name;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------