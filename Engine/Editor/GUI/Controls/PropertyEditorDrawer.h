// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GUI/Controls/PropertyEditors/PropertyEditor.h"

#include <Container/Map.h>
#include <Utility/TypeID.h>

// ------------------------------------------------------------

namespace ost
{
    class PropertyEditorDrawer
    {
    public:
        PropertyEditorDrawer();

        template <typename T>
        void Draw(const char* name, T& value)
        {
            Draw(TypeID::Get<T>(), name, &value);
        }
        void Draw(TypeID type, const char* name, void* pValue);

    private:
        Map<TypeID, PropertyEditor*> _editors;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------