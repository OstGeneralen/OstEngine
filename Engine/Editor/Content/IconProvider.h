/* // Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <GraphicsEngine/Resources/ObjectHandles.h>
#include <GraphicsEngine/Resources/ITexture.h>
#include <Math/Vector2.h>

// ------------------------------------------------------------

namespace ost
{
    enum class EIcon
    {
        Folder,
        File,
        ImgFile,
        Add,
        Actor,
        Scene,
        Restart,
        Play,
        PlayPause,
        Settings,
        COUNT,
    };

    class IconProvider
    {
    public:
        IconProvider();

        void DrawIcon( EIcon icon, const Vector2f& size ) const;
    private:
        void LoadIconAtlas(const char* path );
        void SetIconUV( EIcon icon, const Vector2u& imageLocation );
        
        Vector2f GetIconUVSize() const;
        
        Float32 _pixelsPerIcon;
        Vector2f _atlasSize;


        HTexture _iconTextureHandle;
        Vector2f _iconUVs[static_cast<SizeType>( EIcon::COUNT )];

    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------ */