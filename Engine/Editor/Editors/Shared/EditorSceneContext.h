// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>
#include <string>

#include <Engine/World/Actor.h>
#include <Engine/World/IScene.h>

// ------------------------------------------------------------

namespace ost
{
    struct EditorContext;

    class EditorSceneContext
    {
    public:
        EditorSceneContext(EditorContext& parentContext);

        // Scene Selection
        void SetActiveScene(IScene* pScene);

        // Actor selection
        SizeType GetSelectedActorIndex() const;
        bool HasSelectedActor() const;
        void SelectActor(SizeType index);
        void ClearActorSelection();
        bool IsActorSelected(SizeType index);

        // Actor editing
        bool IsSelectedActorRenaming() const;
        void StartRenameSelectedActor();
        void CancelActorRename();
        std::string& GetActorRenameBuffer();

        // Access
        SizeType GetNumActors() const;
        const char* GetActorName(SizeType index) const;

        // Actions
        void ApplyActorRename();
        void CreateNewActor();
        void DeleteSelectedActor();
        void AddComponentToSelectedActor(TypeID componentType);
        void RemoveComponentFromSelectedActor(TypeID componentType);

        // Backend access
        List<ComponentData> GetSelectedActorComponents();
        Actor* GetSelectedActorPtr();
        Actor* GetActorPtr(SizeType index);
        IScene* GetScenePtr();

    private:
        EditorContext& _parentContext;

        IScene* _pScene;

        SizeType _selectedActorIndex;
        bool _isRenamingSelected;
        std::string _renameBuffer;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------