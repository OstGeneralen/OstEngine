// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <GraphicsEngine/Resources/ObjectHandles.h>

// ------------------------------------------------------------

namespace ost
{
    class MaterialClass;

    class MaterialInstance
    {
    public:
        MaterialInstance();
        MaterialInstance(const MaterialInstance&) = delete;
        MaterialInstance(MaterialInstance&&) noexcept;
        MaterialInstance(MaterialClass& materialClass, HUniformBuffer propsBufferHandle);

        MaterialInstance& operator=(const MaterialInstance&) = delete;
        MaterialInstance& operator=(MaterialInstance&&) noexcept;

        const MaterialClass& GetClass() const;

        void UpdateClass(MaterialClass* newPtr);

    private:
        MaterialClass* _pClass;
        HUniformBuffer _propertiesBuffer;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------