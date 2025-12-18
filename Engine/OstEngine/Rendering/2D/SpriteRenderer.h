#pragma once
#include <OstEngine/Rendering/2D/SpriteDrawCommand.h>
#include <OstEngine/Rendering/ShaderBundle.h>

#include <vector>

namespace ost
{
    class CSpriteRenderer
    {
    public:
        void Initialize();

        void Draw( const SSprite& aSprite );
        void Render();
    private:
        std::vector<SSpriteDrawCommand> _commands;  
        CShaderBundle _spriteShaderBundle;
        
        SUntypedPtr _perSpriteCbuffer;
        SUntypedPtr _spriteQuadVertexBuffer;
    };
} // namespace ost