#pragma once
#include <OstEngine/Rendering/RenderData/Texture.h>
#include <OstEngine/Math/Transform.h>

namespace ost
{
	struct SSprite
	{
    public:
        CTexture* Texture = nullptr;
        CTransform Transform = {};
	};
}