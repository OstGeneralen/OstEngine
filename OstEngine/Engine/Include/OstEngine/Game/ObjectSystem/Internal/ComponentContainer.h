// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/Game/ObjectSystem/Internal/StableIndexedTypeContainerBase.h>

// ------------------------------------------------------------

namespace ost
{
	class CComponent;
	struct SComponentHandle;

	class CComponentContainerBase : public CStableIndexedTypeContainerBase
	{
	public:
		virtual ~CComponentContainerBase() = default;
		
		virtual CComponent& GetComponent(SStableIndex h) = 0;
		virtual const CComponent& GetComponent(SStableIndex idx) const = 0;

		virtual uint64 DenseComponentCount() const = 0;
		virtual CComponent& ComponentAtDenseIndex(uint64 denseIdx) = 0;
	};

}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------