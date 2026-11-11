// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Rendering/IRenderQueue.h"
#include "Rendering/RenderCommand.h"
#include "Resources/GraphicsResourceManager.h"

#include <Container/Map.h>
#include <Container/List.h>

// ------------------------------------------------------------

namespace ost
{
    class RenderQueue : public IRenderQueue
    {
    public:
        RenderQueue(const GraphicsResourceManager& resourceManager);

    public: // IRenderQueue
        void SetView(const Matrix4x4& viewProjection, const Matrix4x4& viewInverse) override;
        void AddLight(const LightData& light) override;
        void Push(const DrawCommand& cmd) override;
        void Finalise() override;

        void Clear() override;

        const RenderView& GetView() const;
        const List<LightData>& GetLights() const;
        const List<RenderCommand>& GetRenderCommands() const;

    private:
        const GraphicsResourceManager& _resourceManager;

        RenderView _view;
        List<RenderCommand> _commands;
        List<DrawCommand> _pendingCommands;

        List<LightData> _lights;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------