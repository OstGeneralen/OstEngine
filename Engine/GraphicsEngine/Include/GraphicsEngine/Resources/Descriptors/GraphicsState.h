// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/GraphicsTypes.h"
#include "GraphicsEngine/Rendering/Vertex.h"
#include "GraphicsEngine/Resources/Descriptors/ShaderDesc.h"
#include "GraphicsEngine/Resources/ObjectHandles.h"
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
            ivals[0] = (Uint64)blendState;
            ivals[1] = (Uint64)vsHandle;
            ivals[2] = (Uint64)psHandle;
            ivals[3] = (SizeType)vertexType;
            ivals[4] = (SizeType)primitiveTopology;
            return hash::fnv1a<5>(ivals);
        }

        EVertexType vertexType;

        HShader vsHandle;
        HShader psHandle;

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