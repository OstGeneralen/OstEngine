// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>
#include <string>

#include <Engine/World/Actor.h>

// ------------------------------------------------------------

namespace ost
{
    struct EditorContext;
    class Scene;

    class EditorSceneContext
    {
    public:
        EditorSceneContext(EditorContext& parentContext);

        // Scene Selection
        void SetActiveScene(Scene* pScene);

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
        List<ComponentData>& GetSelectedActorComponents();
        Actor* GetSelectedActorPtr();
        Actor* GetActorPtr(SizeType index);
        Scene* GetScenePtr();

    private:
        EditorContext& _parentContext;

        Scene* _pScene;
        List<ComponentData> _selectedActorComponents;
        
        SizeType _selectedActorIndex;
        bool _isRenamingSelected;
        std::string _renameBuffer;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------