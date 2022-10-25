// OstEngine (c) - Kasper Esbjornsson 2022

#include "ServiceProvider.h"

#include <Common/Public/Debugging/Logging/Logging.h>

using namespace ost;

DEFINE_LOG( ServiceProviderLog );

IService* ost::CServiceProvider::GetService( size_t serviceTypeId )
{
	auto service = _serviceRegistry.find( serviceTypeId );
	return service == _serviceRegistry.end() ? nullptr : service->second;
}

void ost::CServiceProvider::RegisterService( IService* service, size_t serviceTypeId )
{
	if ( _serviceRegistry.find( serviceTypeId ) != _serviceRegistry.end() )
	{
		LOG_ERROR( ServiceProviderLog, "Tried registering service with ID '{}' when it was already registered", serviceTypeId );
		return;
	}

	_serviceRegistry.emplace( serviceTypeId, service );
	LOG_CONFIRM( ServiceProviderLog, "Registered service with ID '{}'", serviceTypeId );
}

bool ost::CServiceProvider::HasService( size_t serviceTypeId ) const
{
	return _serviceRegistry.contains( serviceTypeId );
}

void ost::CServiceProvider::RemoveService( size_t serviceTypeId )
{
	auto found = _serviceRegistry.find( serviceTypeId );

	if ( found != _serviceRegistry.end() )
	{
		delete found->second;
		_serviceRegistry.erase( found );
	}
	else
	{
		LOG_WARNING( ServiceProviderLog, "Tried removing a service that wasn't registered. ID: '{}'", serviceTypeId );
	}
}
