#include <Windows.h>
#include <Engine/OstEngine.h>
#include <GraphicsEngine/GraphicsEngine.h>


// Forward declare the window procedure
LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

bool running = true;

int main()
{
    // Open the app window
    WNDCLASS windowClass = {};
    windowClass.hInstance = GetModuleHandle(NULL);
    windowClass.style = CS_VREDRAW | CS_HREDRAW;
    windowClass.lpfnWndProc = &WindowProc;
    windowClass.lpszClassName = "AppWindowClass";
    RegisterClass(&windowClass);

    HWND window = CreateWindow("AppWindowClass", "AppWindow", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1600, 900, NULL, NULL, GetModuleHandle(NULL), NULL);
    ShowWindow(window, SW_NORMAL);
    UpdateWindow(window);

    ost::OstEngine engine;
    ost::GraphicsEngine& gfxEngine = engine.GetGraphicsEngine();

    ost::GraphicsEngineSettings gfxEngineSettings;
    gfxEngineSettings.output.clientSize = {1600, 900};
    gfxEngineSettings.output.nativeWindowHandle = window;
    gfxEngineSettings.output.renderSize = {1,1};
    gfxEngineSettings.renderer.clearColor = ost::Colors::Red;
    
    gfxEngine.Initialize( gfxEngineSettings );
    

    while (running)
    {
        MSG msg = {};
        while (PeekMessage(&msg, window, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        gfxEngine.DoRender();
    }


    DestroyWindow(window);
    UnregisterClass("AppWindowClass", GetModuleHandle(NULL));
    return 0;
}

LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {
    case WM_CLOSE: {
        running = false;
        return 0;
    }
    }

    return DefWindowProc(hwnd, msg, wparam, lparam);
}