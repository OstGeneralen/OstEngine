// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <GraphicsEngine/Resources/ITexture.h>
#include <GraphicsEngine/Resources/ObjectHandles.h>
#include <Math/Vector2.h>

// ------------------------------------------------------------

namespace ost
{
    class IGraphicsResourceManager;

    enum class EIcon
    {
        Folder,
        File,
        Image,
        Shader,
        Audio,
        Material,
        Actor,
        Model,
        Settings,
        COUNT,
    };

    class IconProvider
    {
    public:
        IconProvider(IGraphicsResourceManager& gfxResourceManager);

        void DrawIcon(EIcon icon, const Vector2f& size) const;

    private:
        void LoadIconAtlas(const char* path, IGraphicsResourceManager& gfxResourceManager);
        void SetIconUV(EIcon icon, const Vector2u& imageLocation);

        Vector2f GetIconUVSize() const;

        const Uint32 _pixelsPerIcon = 96;
        const Float32 _uvMultiplier = 1.0f / static_cast<Float32>(_pixelsPerIcon);
        Vector2f _atlasSize;

        const void* _pNativeAtlasTexture;
        Vector2f _iconUVs[static_cast<SizeType>(EIcon::COUNT)];
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------