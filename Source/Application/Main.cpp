#include <Windows.h>


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

    ost::RenderHardwareInterface rhi;
    rhi.InitializeForWindow(window);

    ost::ShaderResource vertexShader = rhi.CreateVertexShader(vertexShaderBytecode);
    ost::ShaderResource pixelShader = rhi.CreatePixelShader(pixelShaderBytecode);

    const std::vector<ost::Vertex> meshVertices = {
        {{-1, -1, 0}, ost::colours::Red},
        {{0, 1, 0}, ost::colours::Green},
        {{1, -1, 0}, ost::colours::Blue},
    };
    const std::vector<Uint32> meshIndices = {0, 1, 2};

    ost::MeshResource triangleMesh = rhi.CreateMesh(meshVertices, meshIndices);

    while (running)
    {
        MSG msg = {};
        while (PeekMessage(&msg, window, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        rhi.Clear();

        rhi.Draw(triangleMesh, vertexShader, pixelShader);

        rhi.Present();
    }

    rhi.Shutdown();

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