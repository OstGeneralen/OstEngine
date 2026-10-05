// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>

// ------------------------------------------------------------

namespace ost
{
    class GraphicsResourceManager;

    template <typename T>
    struct GfxHandle
    {
        friend GraphicsResourceManager;

    public:
        GfxHandle()
            : _index{-1ull}
        {
        }
        GfxHandle(const GfxHandle&) = default;

        GfxHandle& operator=(const GfxHandle&) = default;

        bool IsValid() const
        {
            return _index != -1ull;
        }

        operator bool() const
        {
            return IsValid();
        }

        explicit operator SizeType() const
        {
            return _index;
        }

    private:
        GfxHandle(SizeType idx)
            : _index{idx}
        {
        }
        SizeType _index;
    };

    using TextureHandle = GfxHandle<struct HNDType_Texture>;
    using MaterialHandle = GfxHandle<struct HNDType_Material>;
    using ModelHandle = GfxHandle<struct HNDType_Model>;
    using MeshHandle = GfxHandle<struct HNDType_Mesh>;
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------