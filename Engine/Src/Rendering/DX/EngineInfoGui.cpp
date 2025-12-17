#include "EngineInfoGui.h"
#include <Src/ImGui/imgui.h>

void ost::gui::DisplayEngineInfo( const ost::CDXRenderer& aRenderer )
{
    ImGui::SetNextWindowPos( {0, 0} );
    ImGui::Begin( "EngineInfo", NULL,
                  ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove |
                      ImGuiWindowFlags_NoResize );
    ImGui::Text( "DX INFO:" );
    ImGui::Indent( 10.0f );
    ImGui::Text( "GPU: %s", aRenderer.GetDebugInfo().AdapterName.c_str() );
    ImGui::Text( "VRAM: %ugb", aRenderer.GetDebugInfo().VRAM );
    ImGui::Indent( 0 );
    ImGui::End();
}