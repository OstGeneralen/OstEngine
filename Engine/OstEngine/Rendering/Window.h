#pragma once
#include <OstEngine/Types.h>
#include <OstEngine/Math/Vectors.h>
#include <OstEngine/Utility/UntypedPointer.h>
#include <OstEngine/Application/InputReader.h>
#include <functional>

namespace ost
{
	class CWindow;
}

namespace ost
{
	using FEventCallback = std::function< bool( Uint32, Int64, Uint64 )>; 

	class CWindow
	{
	public:
        CWindow();    
		CWindow( const char* aTitle, const Vector2i& aSize, void* aAppInstance );
        ~CWindow();

		CWindow( CWindow&& aOther ) noexcept;
        CWindow& operator=( CWindow&& aRhs ) noexcept;

		CWindow( const CWindow& ) = delete;
        CWindow& operator=( const CWindow& ) = delete;

		void RunEventLoop();
        void BindEventCallback( FEventCallback aCallback );
        FEventCallback EventCallbackFunction();

        void Close();
		bool IsOpen() const;
		
		SUntypedPtr GetWindowPointer();

		const Vector2i& GetSize() const;
	private:
        FEventCallback _eventProcessorFunction = nullptr;
        SUntypedPtr _winPtr;
        Vector2i _size;
		bool _isOpen;
	};
}