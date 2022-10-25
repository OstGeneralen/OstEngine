// OstEngine (c) - Kasper Esbjornsson 2022

#pragma once

#include <Common/Public/Module/ModuleInterface.h>

namespace ost
{
	class CRenderingModule : public IModule
	{
	public:
		void Load( SEngineContext& context ) override;
		void Unload( SEngineContext& context ) override;
	};
} // namespace ost