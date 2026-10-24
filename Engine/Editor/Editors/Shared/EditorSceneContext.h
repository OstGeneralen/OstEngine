// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>
#include <string>

// ------------------------------------------------------------

namespace ost
{
    struct EditorContext;
    class Scene;
    class Actor;

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

        // Backend access
        Actor* GetActorPtr(SizeType index);
        Scene* GetScenePtr();

    private:
        EditorContext& _parentContext;

        Scene* _pScene;

        SizeType _selectedActorIndex;
        bool _isRenamingSelected;
        std::string _renameBuffer;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------