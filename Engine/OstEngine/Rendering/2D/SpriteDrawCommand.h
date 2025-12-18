#pragma once
#include "OstEngine/Math/Matrix4x4.h"
#include "OstEngine/Utility/UntypedPointer.h"

namespace ost
{
    struct SSprite;

	struct SSpriteDrawCommand
	{
        SSpriteDrawCommand() = default;
        SSpriteDrawCommand( const SSpriteDrawCommand& ) = default;
        SSpriteDrawCommand( const SSprite& aFromSprite );

        TMatrix4x4<float> ModelMatrix;
        SUntypedPtr TextureResource;
	};
}