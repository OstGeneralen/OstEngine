#pragma once
#include <OstEngine/Types.h>
#include <OstEngine/Math/Vectors.h>

struct SDL_Window;

namespace ost
{
	class CWindow
	{
	public:
        CWindow();    
		CWindow( const char* aTitle, const Vector2i& aSize );
        ~CWindow();

		CWindow( CWindow&& aOther ) noexcept;
        CWindow& operator=( CWindow&& aRhs ) noexcept;

		CWindow( const CWindow& ) = delete;
        CWindow& operator=( const CWindow& ) = delete;

		void RunEventLoop();

		bool IsOpen() const;
	private:
        SDL_Window* _winPtr;
        bool _isOpen;
	};
}