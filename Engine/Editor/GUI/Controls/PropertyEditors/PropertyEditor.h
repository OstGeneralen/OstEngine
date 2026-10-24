// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Utility/TypeID.h>

// ------------------------------------------------------------

namespace ost
{
    class PropertyEditor
    {
    public:
        virtual ~PropertyEditor() = default;
        virtual TypeID PropertyTypeID() const = 0;
        virtual void DisplayGeneric(const char* name, void* data) = 0;
    };

    template <typename T>
    class PropertyTypeEditor : public PropertyEditor
    {
    public:
        TypeID PropertyTypeID() const override
        {
            return TypeID::Get<T>();
        }

        virtual void Display(const char* name, T& data) = 0;

    private:
        void DisplayGeneric(const char* name, void* data) override final
        {
            Display(name, *static_cast<T*>(data));
        }
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------