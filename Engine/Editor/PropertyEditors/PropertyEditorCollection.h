// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "PropertyEditors/PropertyEditor.h"

#include <Container/Map.h>
#include <Memory/UniquePtr.h>
#include <Utility/TypeID.h>

// ------------------------------------------------------------

namespace ost
{
    class UnsupportedPropertyEditor : public PropertyEditor
    {
        TypeID GetTargetTypeID() const override
        {
            return TypeID::Get<Uint32>();
        }
    };

    class PropertyEditorCollection
    {
    public:
        template <typename T>
        void RegisterEditor()
        {
            UniquePtr<PropertyEditor> editor = Ptr::NewUnique<T>();
            _typeToEditor.Insert(editor->GetTargetTypeID(), std::move(editor));
        }

        template <typename T>
        void DisplayEditor(const char* name, T& property)
        {
            if (UniquePtr<PropertyEditor>* found = _typeToEditor.TryGetValue(TypeID::Get<T>()))
            {
                (*found)->Display(name, &property);
            }
            else
            {
                _unsupported.Display(name, nullptr);
            }
        }

    private:
        Map<TypeID, UniquePtr<PropertyEditor>> _typeToEditor;
        UnsupportedPropertyEditor _unsupported;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------