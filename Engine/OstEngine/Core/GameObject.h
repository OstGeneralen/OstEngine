#pragma once
#include "OstEngine/Math/Transform.h"

namespace ost
{
	class CGameObject
	{
    public:
        CTransform Transform;

		virtual ~CGameObject() = default;
	};
}