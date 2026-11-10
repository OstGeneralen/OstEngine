// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>

#include <Memory/Memory.h>
#include <Utility/Assert.h>
#include <Utility/TypeID.h>
#include <string>

// ------------------------------------------------------------

namespace ost
{
    class MaterialProperty
    {
    public:
        template <typename T>
        void Set(const T& value)
        {
            OST_ASSERT(_typeID == TypeID::Get<T>(), "Type must match");
            MemCopy(_pMemory, &value, _dataSize);
        }

        template <typename T>
        const T& Get() const
        {
            OST_ASSERT(_typeID == TypeID::Get<T>(), "Type must match");
            return *static_cast<const T*>(_pMemory);
        }

    public:
        MaterialProperty(const std::string& name, TypeID typeID, SizeType dataSize, void* pMemory);

        const std::string& GetName() const;

    private:
        std::string _name;
        TypeID _typeID;
        SizeType _dataSize;
        void* _pMemory;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------