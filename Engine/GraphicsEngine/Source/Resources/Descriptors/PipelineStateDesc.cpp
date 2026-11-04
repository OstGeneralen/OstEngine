// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GraphicsEngine/Resources/Descriptors/PipelineStateDesc.h"

using namespace ost;

// ------------------------------------------------------------

List<VertexElement> ost::PipelineStateDesc::DefaultVertexLayout_Surface()
{
    return {
        {"POSITION", EDataSize::Float4}, // Pos
        {"NORMAL", EDataSize::Float3},   // Nor
        {"TANGENT", EDataSize::Float3},  // Tan
        {"COLOR", EDataSize::Float4},    // Vertex Color
        {"TEXCOORD", EDataSize::Float2}  // UV
    };
}

List<VertexElement> ost::PipelineStateDesc::DefaultVertexLayout_Blit()
{
    return {
        {"POSITION", EDataSize::Float4}, // Pos
        {"TEXCOORD", EDataSize::Float2}  // UV
    };
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------