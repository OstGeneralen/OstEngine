// Kasper "OstGeneralen" Esbjornsson - 2026
#include "AddComponentPromptWindow.h"

#include "Editors/PropertyEditor/Commands/ComponentCommands.h"

#include <Engine/World/IComponentFactory.h>

using namespace ost;

// ------------------------------------------------------------

void AddComponentPromptWindow::DrawGUI(EditorContext& context)
{
    IComponentFactory& componentFactory = context.serviceLocator.GetRequired<IComponentFactory>();
    const auto& componentTypes = componentFactory.GetRegisteredTypesInfo();

    OstGui::SetNextWindowPos(Vector2f(OstGui::GetMainViewport()->Size) * 0.5f, 0, {0.5f, 0.5f});
    OstGui::SetNextWindowSize({200, 500});

    bool open = true;

    OstGui::Begin("Add Component", &open, ImGuiWindowFlags_NoResize);

    for (const auto& typeInfo : componentTypes)
    {
        OstGui::BeginDisabled(context.sceneContext.GetSelectedActorPtr()->GetComponent(typeInfo.typeId) != nullptr);

        if (OstGui::Button(typeInfo.typeName.c_str(), {OstGui::GetContentRegionAvail().x, 0}))
        {
            context.commandQueue.PushCommand(Ptr::NewUnique<AddComponentEditorCommand>(typeInfo.typeId));
            open = false;
        }

        OstGui::EndDisabled();
    }

    OstGui::End();

    if (!open)
    {
        context.guiContext.CloseWindow<AddComponentPromptWindow>();
    }
}

// ------------------------------------------------------------

EGuiWindowMode AddComponentPromptWindow::GetWindowMode() const
{
    return EGuiWindowMode::Modal;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------