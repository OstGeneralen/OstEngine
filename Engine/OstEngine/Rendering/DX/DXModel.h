#pragma once
#include <OstEngine/OstEngineMinimal.h>
#include <OstEngine/Math/Color.h>
#include <OstEngine/Math/Vectors.h>
#include <OstEngine/Rendering/RenderData/Vertex.h>

#include <vector>

struct ID3D11Resource;
struct ID3D11Buffer;

namespace ost
{
    class CDXModel
    {
    public:
        CDXModel& AddVertex( const Vector4f& aVertPos, const SColor& aVertColor );
        void InitializeResource();

        void Render();
    private:
        std::vector<SVertex_Pos4_Col4> _vertices;
        ID3D11Buffer* _dxVertexBuffer;
    };
} // namespace ost