// OstEngine (c) - Kasper Esbjornsson 2022

#pragma once
#include <Common/Public/Module/ModuleInterface.h>

#include <string>

namespace ost
{
	struct SModuleHandle
	{
	public:
		static SModuleHandle MakeInvalid()
		{
			return SModuleHandle( "", nullptr, nullptr );
		}

		std::string ModuleName;
		IModule* ModulePtr;
		void* InstancePtr;

		SModuleHandle()
			: ModuleName( "" )
			, ModulePtr( nullptr )
			, InstancePtr( nullptr )
		{
		}

		SModuleHandle( const std::string& name, IModule* modulePtr, void* instancePtr )
			: ModuleName( name )
			, ModulePtr( modulePtr )
			, InstancePtr( instancePtr )
		{
		}

		SModuleHandle( SModuleHandle&& r ) noexcept
			: ModuleName( r.ModuleName )
			, ModulePtr( r.ModulePtr )
			, InstancePtr( r.InstancePtr )
		{
			r.ModulePtr = nullptr;
			r.InstancePtr = nullptr;
		}

		SModuleHandle( const SModuleHandle& ) = delete;

		bool IsValid() const
		{
			return ModulePtr && InstancePtr;
		}

		void operator=( SModuleHandle&& r ) noexcept
		{
			ModuleName = r.ModuleName;
			ModulePtr = r.ModulePtr;
			InstancePtr = r.InstancePtr;

			r.ModulePtr = nullptr;
			r.InstancePtr = nullptr;
		}
	};
} // namespace ost