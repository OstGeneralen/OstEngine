#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

// ------------------------------------------------------------

int main( int aArgCount, char* aArgs[] )
{
    SDL_Window* winPtr;
    SDL_Renderer* rendererPtr;
    bool run = SDL_CreateWindowAndRenderer( "Title", 800, 800, SDL_WINDOW_INPUT_FOCUS, &winPtr, &rendererPtr );
    SDL_SetRenderDrawColor( rendererPtr, 50, 150, 255, 255 );

    while ( run )
    {
        SDL_Event e;
        while ( SDL_PollEvent( &e ) )
        {
            if ( e.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED )
            {
                run = false;
            }
        }

        SDL_RenderClear( rendererPtr );
        SDL_RenderPresent( rendererPtr );
    }

    SDL_DestroyRenderer( rendererPtr );
    SDL_DestroyWindow( winPtr );
    return 0;
}

// ------------------------------------------------------------
