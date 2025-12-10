#pragma once
#include <OstEngine/Math/Color.h>
#include <OstEngine/Math/Rect.h>
#include <OstEngine/Math/Vectors.h>
#include <OstEngine/Rendering/Sprite/Texture.h>
#include <OstEngine/Utility/UntypedPointer.h>

namespace ost
{
    struct SSprite
    {
        void Create( STexture& aTexture );
        void Create( STexture& aTexture, const Rectf& aRect );

        Vector2f Location;
        Rectf SourceRect;
        SUntypedPtr BackendTexturePtr;
        SColor DrawColor;
    };
} // namespace ost