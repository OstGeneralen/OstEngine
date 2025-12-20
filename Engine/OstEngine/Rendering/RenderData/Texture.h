#pragma once
#include <string>
#include "OstEngine/Common/Utility/UntypedPointer.h"
#include "OstEngine/Common/Math/Vector2.h"

// ------------------------------------------------------------

namespace ost
{
	class CTexture
	{
	public:
        void LoadDDS( const std::string& aPath );
        const Vector2u& GetDimensions() const;

		SUntypedPtr GetTextureResource() const;

	private:
        SUntypedPtr _texResView;
        Vector2u _dimensions;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------