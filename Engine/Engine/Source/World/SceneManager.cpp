// Kasper "OstGeneralen" Esbjornsson - 2026
#include "SceneManager.h"

using namespace ost;

// ------------------------------------------------------------

Scene* SceneManager::CreateScene()
{
    return _scenes.Add(new Scene(_gameWorld));
}

void SceneManager::SetActiveScene(Scene* pScene)
{
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

const Scene* SceneManager::GetActiveScene() const
{
    if (_activeSceneIndex == _scenes.Npos)
    {
        return nullptr;
    }
    return _scenes[_activeSceneIndex];
}

// ------------------------------------------------------------

GameWorld& ost::SceneManager::GetGameWorld()
{
    return _gameWorld;
}

// ------------------------------------------------------------

Scene* ost::SceneManager::GetActiveScene()
{
    if (_activeSceneIndex == _scenes.Npos)
    {
        return nullptr;
    }
    return _scenes[_activeSceneIndex];
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------