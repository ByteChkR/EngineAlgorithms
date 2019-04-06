#include "CollisionManager.h"
#include "StaticOBBCollider.h"
#include "mge/core/GameObject.hpp"
#include "Debug.h"
#include "glm.hpp"
#include "QuadTree.h"
#include <vector>

std::vector<Collider*> CollisionManager::_activeCollider = std::vector<Collider*>();
OctTree* CollisionManager::_staticColliderTree = OctTree::createTree();
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
	OctTree::ResetColliderHit(_staticColliderTree);


	for (size_t i = 0; i < _activeCollider.size(); i++)
	{

		for (size_t j = 0; j < _activeCollider.size(); j++)
		{


			if(j <= i ||!_activeCollider[i]->CheckCirlce(_activeCollider[j]))continue; //From 550.000 checks to ~1000

			actualChecks++;
			if (_activeCollider[i]->Check(_activeCollider[j]))
			{
				_activeCollider[i]->SetHit(true);
				_activeCollider[j]->SetHit(true);
				//HIT
			}
		}

		OctTree* senode = OctTree::getSmallestEnclosement(_staticColliderTree, _activeCollider[i]);
		std::vector<Collider*> closeCollider = OctTree::getPossiblyCollidingColliders(senode);

		for (size_t j = 0; j < closeCollider.size(); j++)
		{
			if (!_activeCollider[i]->CheckCirlce(closeCollider[j]))continue; //From 550.000 checks to ~1000

			actualChecks++;
			if (_activeCollider[i]->Check(closeCollider[j]))
			{
				_activeCollider[i]->SetHit(true);
				closeCollider[j]->SetHit(true);
				//HIT
			}
		}

	}


	return actualChecks;



}