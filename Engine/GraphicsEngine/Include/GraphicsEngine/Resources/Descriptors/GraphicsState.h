// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/GraphicsTypes.h"
#include "GraphicsEngine/Rendering/Vertex.h"
#include "GraphicsEngine/Resources/Descriptors/ShaderDesc.h"
#include "GraphicsEngine/Resources/VertexElement.h"
#include "Objects/Shader.h"

#include <Container/List.h>
#include <Memory/BufferView.h>
#include <Utility/Hash.h>

// ------------------------------------------------------------

namespace ost
{
    struct GraphicsState
    {
        inline Uint64 CalculateHash() const
        {
            Uint64 ivals[5];
            ivals[0] = (intptr_t)vsBytecodeView.Data();
            ivals[1] = (intptr_t)psBytecodeView.Data();
            ivals[2] = (SizeType)blendState;
            ivals[3] = (SizeType)vertexType;
            ivals[4] = (SizeType)primitiveTopology;
            return hash::fnv1a<5>(ivals);
        }

        ERenderPath renderPath; // Deferred? Forward? etc.
        EVertexType vertexType; // Static, Blit, e

        BufferView vsBytecodeView;
        BufferView psBytecodeView;

        EBlendState blendState;
        EPrimitiveTopology primitiveTopology;
    };
} // namespace ost

// ------------------------------------------------------------

namespace std
{
    template <>
    struct hash<ost::GraphicsState>
    {
        size_t operator()(const GraphicsState& gs) const
        {
            return static_cast<SizeType>(gs.CalculateHash());
        }
    };
} // namespace std

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------