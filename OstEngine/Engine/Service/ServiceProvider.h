#pragma once

#include <Common/Public/Engine/Service/ServiceProviderInterface.h>
#include <unordered_map>

namespace ost
{
	class CServiceProvider : public IServiceProvider
	{
	private:
		IService* GetService(size_t serviceTypeId) override;
		void RegisterService(IService* service, size_t serviceTypeId) override;
		bool HasService(size_t serviceTypeId) const override;
		void RemoveService(size_t serviceTypeId) override;

		std::unordered_map<size_t, IService*> _serviceRegistry;
	};
}