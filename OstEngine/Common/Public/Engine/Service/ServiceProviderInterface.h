// OstEngine (c) - Kasper Esbjornsson 2022

#pragma once
#include "Common/Public/Engine/Service/ServiceInterface.h"

#include <typeinfo>

namespace ost
{
	class IServiceProvider
	{
	public:
		template < typename T, typename... TArgs >
		void EmplaceService( TArgs&&... args )
		{
			RegisterService( new T( args... ), typeid( T ).hash_code() );
		}

		template < typename T >
		void RegisterService( T* s )
		{
			RegisterService( s, typeid( T ).hash_code() );
		}

		template < typename T >
		T* GetService()
		{
			return static_cast< T* >( GetService( typeid( T ).hash_code() ) );
		}

		template < typename T >
		bool HasService() const
		{
			return HasService( typeid( T ).hash_code() );
		}

		template < typename T >
		void RemoveService()
		{
			RemoveService( typeid( T ).hash_code() );
		}

	protected:
		virtual IService* GetService( size_t serviceTypeId ) = 0;
		virtual void RegisterService( IService* service, size_t serviceTypeId ) = 0;
		virtual bool HasService( size_t serviceTypeId ) const = 0;
		virtual void RemoveService( size_t serviceTypeId ) = 0;
	};
} // namespace ost