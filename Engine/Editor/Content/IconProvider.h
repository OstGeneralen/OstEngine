// Kasper "OstGeneralen" Esbjornsson - 2026
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
        Up,
        COUNT,
    };

    class IconProvider
    {
    public:
        IconProvider();

        
        const ITexture& GetIcon( EIcon icon ) const;
        void DrawGUIIcon( EIcon icon, const Vector2f& size ) const;
    private:
        void LoadImageIcon( EIcon icon, const char* path );

        HTexture _iconTextureHandles[static_cast<SizeType>(EIcon::COUNT)];

    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------