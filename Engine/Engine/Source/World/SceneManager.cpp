// Kasper "OstGeneralen" Esbjornsson - 2026
#include "SceneManager.h"

#include "Scene.h"

using namespace ost;

// ------------------------------------------------------------

IScene* SceneManager::CreateScene()
{
    return _scenes.Add(new Scene());
}

void SceneManager::SetActiveScene(IScene* pSceneInterface)
{
    Scene* pScene = static_cast<Scene*>(pSceneInterface);

    _activeSceneIndex = _scenes.Npos;

    for (SizeType i = 0; i < _scenes.GetSize(); ++i)
    {
        if (_scenes[i] == pScene)
        {
            _activeSceneIndex = i;
            break;
        }
    }
}

IScene* ost::SceneManager::GetActiveScene()
{
    if (_activeSceneIndex == _scenes.Npos)
    {
        return nullptr;
    }
    return _scenes[_activeSceneIndex];
}

const IScene* SceneManager::GetActiveScene() const
{
    if (_activeSceneIndex == _scenes.Npos)
    {
        return nullptr;
    }
    return _scenes[_activeSceneIndex];
}

// ------------------------------------------------------------

SceneGraph& ost::SceneManager::GetActiveSceneGraph()
{
    return _scenes[_activeSceneIndex]->GetSceneGraph();
}

void ost::SceneManager::Tick(ServiceLocator& serviceLocator)
{
    _scenes[_activeSceneIndex]->Tick(serviceLocator);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------