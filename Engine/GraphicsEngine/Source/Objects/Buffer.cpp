// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Buffer.h"

#include "RHI/RHIInternal.h"

using namespace ost;

// ------------------------------------------------------------

Buffer::Buffer() = default;
Buffer::Buffer(const Buffer&) = default;
Buffer::~Buffer() = default;

void ost::Buffer::SetDebugName(const std::string& n) const
{
    if (_buffer)
    {
        _buffer->SetPrivateData(WKPDID_D3DDebugObjectName, n.length(), n.data());
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------