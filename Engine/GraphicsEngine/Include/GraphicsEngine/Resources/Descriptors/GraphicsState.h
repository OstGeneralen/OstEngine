// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/GraphicsTypes.h"
#include "GraphicsEngine/Rendering/Vertex.h"
#include "GraphicsEngine/Resources/Descriptors/ShaderDesc.h"
#include "GraphicsEngine/Resources/VertexElement.h"

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
            ivals[0] = (intptr_t)vsBytecode.Data();
            ivals[1] = (intptr_t)psBytecode.Data();
            ivals[2] = (SizeType)blendState;
            ivals[3] = (SizeType)vertexType;
            ivals[4] = (SizeType)primitiveTopology;
            return hash::fnv1a<5>(ivals);
        }

        BufferView vsBytecode;
        BufferView psBytecode;

        ERenderPath renderPath;
        EBlendState blendState;
        EVertexType vertexType;
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