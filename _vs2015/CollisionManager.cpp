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

void CollisionManager::CheckCollisions()
{
	 //Improvement 2: Add Continue to loop to prevent checking objects twice

	int collisionsPerFrame = 0;
	int actualChecks = 0;

	for (size_t i = 0; i < _activeCollider.size(); i++)
	{
		_activeCollider[i]->SetHit(false);
	}

	for (size_t i = 0; i < _activeCollider.size(); i++)
	{

		for (size_t j = 0; j < _activeCollider.size(); j++)
		{

			if (j == i)continue; //Prevent checking against itself.
			actualChecks++;

			
			if (_activeCollider[i]->Check(_activeCollider[j]))
			{
				collisionsPerFrame++;
				_activeCollider[i]->SetHit(true);
				_activeCollider[j]->SetHit(true);
				//HIT
			}
		}
	}


	//Debug::Log(std::to_string(actualChecks), DebugLevel::ActualCollisionChecks);
	//Debug::Log(std::to_string(collisionsPerFrame), DebugLevel::CollisionsPerFrame);



}