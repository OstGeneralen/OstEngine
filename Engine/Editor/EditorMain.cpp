// Kasper "OstGeneralen" Esbjornsson - 2026
#include "ImGui/imgui.h"

#include <windows.h>

#include <Engine/Configuration/RuntimeConfig.h>
#include <Engine/Game/GameInterface.h>
#include <Engine/IOstEngine.h>
#include <GraphicsEngine/IGraphicsEngine.h>

// ------------------------------------------------------------

using namespace ost;

// ------------------------------------------------------------

HRESULT WinProc( HWND hwnd, UINT msg, WPARAM wp, LPARAM lp );

// ------------------------------------------------------------

int main()
{
    // Load runtime cfg
    RuntimeConfig config;
    config.LoadFromFile("EditorConfig.json");

    // Create window
    WNDCLASS windowClass = {};
    windowClass.

    GraphicsEngineSettings gfxSettings;
    IGraphicsEngine::CreateNew(gfxSettings);
    
    OstEngineSettings engineSettings;
    engineSettings.assetsCfg = config.assets;
    UniquePtr<IOstEngine> engine = IOstEngine::CreateNew(CreateGameInstance(), engineSettings);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------