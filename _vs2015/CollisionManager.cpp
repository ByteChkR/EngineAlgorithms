#include "CollisionManager.h"
#include "StaticOBBCollider.h"
#include "mge/core/GameObject.hpp"
#include "Debug.h"
#include "glm.hpp"
#include <vector>

std::vector<Collider*> CollisionManager::_activeCollider = std::vector<Collider*>();
CollisionManager* CollisionManager::instance = nullptr;
CollisionManager::CollisionManager()
{
	instance = this;
}

CollisionManager::~CollisionManager()
{
}

int CollisionManager::CheckCollisions()
{

	int collisionsPerFrame = 0;
	int actualChecks = 0;

	for (size_t i = 0; i < _activeCollider.size(); i++)
	{
		_activeCollider[i]->SetHit(false);
	}



	for (size_t i = 0; i < _activeCollider.size(); i++)
	{
		if (_activeCollider[i]->IsStatic())continue;
		for (size_t j = 0; j < _activeCollider.size(); j++)
		{

			if (j <= i)continue; //Prevent checking against itself. From 1.000.000 checks to 550.000 checks

			if(!_activeCollider[i]->CheckCirlce(_activeCollider[j]))continue; //From 550.000 checks to ~1000

			actualChecks++;
			if (_activeCollider[i]->Check(_activeCollider[j]))
			{
				_activeCollider[i]->SetHit(true);
				_activeCollider[j]->SetHit(true);
				//HIT
			}
		}
	}


	return actualChecks;



}