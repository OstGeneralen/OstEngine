#pragma once
#include "OstEngine/Common/Math/Matrix4x4.h"
#include "OstEngine/Common/Utility/UntypedPointer.h"

namespace ost
{
    struct SSprite;

	struct SSpriteDrawCommand
	{
        SSpriteDrawCommand() = default;
        SSpriteDrawCommand( const SSpriteDrawCommand& ) = default;
        SSpriteDrawCommand( const SSprite& aFromSprite );

        Matrix4x4 ModelMatrix;
        SUntypedPtr TextureResource;
	};
}