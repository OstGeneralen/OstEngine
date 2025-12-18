#include "OstEngine/Rendering/2D/SpriteDrawCommand.h"
#include "OstEngine/Rendering/2D/Sprite.h"

// ------------------------------------------------------------

ost::SSpriteDrawCommand::SSpriteDrawCommand( const SSprite& aFromSprite )
{
    ModelMatrix = aFromSprite.Transform.GetMatrix();
    TextureResource = aFromSprite.Texture->GetTextureResource();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------