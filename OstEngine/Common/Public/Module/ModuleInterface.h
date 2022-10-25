#pragma once
#include "Common/Public/Engine/EngineContext.h"

namespace ost
{
	class IModule
	{
	public:
		virtual ~IModule() {}
		virtual void Load(SEngineContext&) = 0;
		virtual void Unload(SEngineContext&) = 0;
	};
}