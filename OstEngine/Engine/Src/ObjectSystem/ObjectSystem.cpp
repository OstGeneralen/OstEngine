// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include <ObjectSystem/ObjectSystem.h>

// ------------------------------------------------------------

ost::CComponentTypeRegistry& ost::CObjectSystem::GetComponentTypeRegistry()
{
	return _componentTypeRegistry;
}

// ------------------------------------------------------------

ost::TPtr<ost::CScene> ost::CObjectSystem::CreateScene(bool makeActive)
{
	if (makeActive)
	{
		_activeScene = _scenes.Emplace(_componentTypeRegistry);
		return _activeScene;
	}

	return _scenes.Emplace(_componentTypeRegistry);
}

// ------------------------------------------------------------

void ost::CObjectSystem::SetActiveScene(TPtr<CScene> scene)
{
	_activeScene = scene;
}

// ------------------------------------------------------------

void ost::CObjectSystem::TickActiveScene()
{
	if (_activeScene.Valid())
	{
		_activeScene->Tick();
	}
}

// ------------------------------------------------------------

void ost::CObjectSystem::SweepUnreferenced()
{
	// Todo: Iterate scenes and remove any objects that are no longer referenced
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------