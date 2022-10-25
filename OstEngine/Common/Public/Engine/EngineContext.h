#pragma once
#include "Common/Public/Engine/Service/ServiceProviderInterface.h"

namespace ost
{
	struct SEngineContext
	{
		SEngineContext(IServiceProvider& serviceProvider)
			: ServiceProvider(serviceProvider)
		{
		}

		IServiceProvider& ServiceProvider;
	};
}