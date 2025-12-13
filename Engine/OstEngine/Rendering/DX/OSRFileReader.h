#pragma once
#include <OstEngine/Rendering/DX/DXRenderStateDescriptor.h>
#include <string>

namespace ost
{
    class COSRFileReader
    {
    public:
        static bool TryReadFromFile( const std::string& aPath, SDXRenderStateDescriptor& outInto );
    };
}