// Kasper "OstGeneralen" Esbjornsson - 2026
#include "EditorSceneContext.h"

#include "EditorContext.h"

// Game World
#include <Engine/World/Actor.h>
#include <Engine/World/Scene.h>

// Commands
#include "Editors/SceneOutliner/Commands/ActorListEditorCommands.h"
#include "Editors/SceneOutliner/Commands/RenameActorEditorCommand.h"

using namespace ost;

// ------------------------------------------------------------

ost::EditorSceneContext::EditorSceneContext(EditorContext& parentContext)
    : _parentContext{parentContext}
    , _pScene{nullptr}
    , _selectedActorIndex{SizeTypeNpos}
    , _isRenamingSelected{false}
    , _renameBuffer{}
{
}

// ------------------------------------------------------------

void ost::EditorSceneContext::SetActiveScene(Scene* pScene)
{
    _pScene = pScene;

    // Switching scene resets all current actor editing state
    ClearActorSelection();
}

// ------------------------------------------------------------

SizeType ost::EditorSceneContext::GetSelectedActorIndex() const
{
    return _selectedActorIndex;
}

bool ost::EditorSceneContext::HasSelectedActor() const
{
    return _selectedActorIndex != SizeTypeNpos;
}

void ost::EditorSceneContext::SelectActor(SizeType index)
{
    // Selection means we stop whatever renaming we've got ongoing
    CancelActorRename();
    _selectedActorIndex = index;

    _selectedActorComponents = GetActorPtr(index)->GetComponents();
}

void ost::EditorSceneContext::ClearActorSelection()
{
    CancelActorRename();
    _selectedActorIndex = SizeTypeNpos;
    _selectedActorComponents = {};
}

bool ost::EditorSceneContext::IsActorSelected(SizeType index)
{
    return _selectedActorIndex == index;
}

// ------------------------------------------------------------

bool ost::EditorSceneContext::IsSelectedActorRenaming() const
{
    return HasSelectedActor() && _isRenamingSelected;
}

void ost::EditorSceneContext::StartRenameSelectedActor()
{
    if (HasSelectedActor())
    {
        _renameBuffer = _pScene->GetAllActors()[_selectedActorIndex]->GetName().GetString();
        _isRenamingSelected = true;
    }
}

void ost::EditorSceneContext::CancelActorRename()
{
    _isRenamingSelected = false;
    _renameBuffer = "";
}

std::string& ost::EditorSceneContext::GetActorRenameBuffer()
{
    return _renameBuffer;
}

// ------------------------------------------------------------

SizeType ost::EditorSceneContext::GetNumActors() const
{
    if (_pScene == nullptr)
    {
        return 0;
    }
    return _pScene->GetAllActors().GetSize();
}

const char* ost::EditorSceneContext::GetActorName(SizeType index) const
{
    return _pScene->GetAllActors()[index]->GetName().GetString().c_str();
}

// ------------------------------------------------------------

void ost::EditorSceneContext::ApplyActorRename()
{
    _parentContext.commandQueue.PushCommand(Ptr::NewUnique<RenameActorEditorCommand>(_selectedActorIndex, _renameBuffer));
    CancelActorRename();
}

void ost::EditorSceneContext::CreateNewActor()
{
    _parentContext.commandQueue.PushCommand(Ptr::NewUnique<AddNewActorEditorCommand>());
    ClearActorSelection();
}

void ost::EditorSceneContext::DeleteSelectedActor()
{
    _parentContext.commandQueue.PushCommand(Ptr::NewUnique<DeleteActorEditorCommand>(_selectedActorIndex));
    ClearActorSelection();
}

void ost::EditorSceneContext::AddComponentToSelectedActor(TypeID componentType)
{
    GetSelectedActorPtr()->AddComponent(componentType);
    _selectedActorComponents = GetSelectedActorPtr()->GetComponents();
}

void ost::EditorSceneContext::RemoveComponentFromSelectedActor(TypeID componentType)
{
    GetSelectedActorPtr()->RemoveComponent(componentType);
    _selectedActorComponents = GetSelectedActorPtr()->GetComponents();
}

// ------------------------------------------------------------

List<ComponentData>& ost::EditorSceneContext::GetSelectedActorComponents()
{
    return _selectedActorComponents;
}

Actor* ost::EditorSceneContext::GetSelectedActorPtr()
{
    if (_selectedActorIndex == SizeTypeNpos)
    {
        return nullptr;
    }

    return _pScene->GetAllActors()[_selectedActorIndex].Get();
}

Actor* ost::EditorSceneContext::GetActorPtr(SizeType index)
{
    return _pScene->GetAllActors()[index].Get();
}

Scene* ost::EditorSceneContext::GetScenePtr()
{
    return _pScene;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------