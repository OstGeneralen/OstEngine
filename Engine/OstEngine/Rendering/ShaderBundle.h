// ------------------------------------------------------------
// A bundle of VS, PS + Input Layout
// ------------------------------------------------------------
#pragma once
#include "OstEngine/Common/Utility/UntypedPointer.h"

#include <string>

// ------------------------------------------------------------

namespace ost
{
    class CShaderBundle
    {
    public:
        void InitFromFile(const std::string& aPath);

        void BeginUse();

    private:
        SUntypedPtr _psPtr;
        SUntypedPtr _vsPtr;
        SUntypedPtr _ilPtr;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------