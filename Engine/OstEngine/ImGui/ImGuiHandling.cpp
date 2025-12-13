#include "ImGuiHandling.h"

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

#include <OstEngine/Rendering/DX/DXRenderer.h>
#include <OstEngine/Rendering/Window.h>
#include <Windows.h>

void ost::DeveloperGUI::Init( CWindow& aWindow, CDXRenderer& aRenderer )
{
#if ENABLE_GUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui_ImplWin32_Init( aWindow.GetWindowPointer().Get_AsIs<void*>() );
    ImGui_ImplDX11_Init( aRenderer.GetDevicePointer(), aRenderer.GetDeviceContextPointer() );
#endif
}

void ost::DeveloperGUI::Deinit()
{
#if ENABLE_GUI
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
#endif
}

void ost::DeveloperGUI::BeginFrame()
{
#if ENABLE_GUI
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
#endif
}

void ost::DeveloperGUI::EndFrame()
{
#if ENABLE_GUI
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData( ImGui::GetDrawData() );
#endif
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
bool ost::DeveloperGUI::WndProcHandling( CWindow& aWindow, Uint32 aMsg, Int64 wparam, Uint64 lparam )
{
    return ImGui_ImplWin32_WndProcHandler( aWindow.GetWindowPointer().Get_AsIs<HWND>(), aMsg, wparam, lparam );
}