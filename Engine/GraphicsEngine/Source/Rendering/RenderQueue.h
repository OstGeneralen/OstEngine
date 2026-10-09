// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Rendering/IRenderQueue.h"
#include "Rendering/RenderCommand.h"
#include "Resources/GraphicsResourceManager.h"

#include <Container/List.h>

// ------------------------------------------------------------

namespace ost
{
    class RenderQueue : public IRenderQueue
    {
    public:
        RenderQueue(const GraphicsResourceManager& resourceManager);

    public: // IRenderQueue
        void SetView(const Matrix4x4& view) override;
        void Push(ModelCommand&& cmd) override;
        void Push(LightCommand&& cmd) override;
        void Clear() override;

        const Matrix4x4& GetView() const;
        const List<RenderCommand>& GetDrawCommands() const;
        const List<LightCommand>& GetLightCommands() const;

    private:
        const GraphicsResourceManager& _resourceManager;

        Matrix4x4 _view;
        List<RenderCommand> _drawCommands;
        List<LightCommand> _lights;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------