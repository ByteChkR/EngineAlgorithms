#include "CollisionManager.h"
#include "StaticOBBCollider.h"
#include "mge/core/GameObject.hpp"
#include "Debug.h"
#include "glm.hpp"
#include "QuadTree.h"
#include <vector>

std::vector<Collider*> CollisionManager::_activeCollider = std::vector<Collider*>();
std::vector<OctTree*> CollisionManager::_leafNodes = std::vector<OctTree*>();
OctTree* CollisionManager::_staticColliderTree = OctTree::createTree();
CollisionManager* CollisionManager::instance = nullptr;
CollisionManager::CollisionManager()
{
	instance = this;
}

CollisionManager::~CollisionManager()
{
}
int CollisionManager::actualChecks = 0;
int CollisionManager::CheckCollisions()
{




	OctTree::ResetColliderHit(_staticColliderTree);

	for (size_t j = 0; j < _leafNodes.size(); ++j)
	{
		_leafNodes[j]->dynamicCollder.clear();
		//Check if dynamic collider is still in leaf node.
		//if not push up the tree until it intersects. then go backwards into the tree again.
	}

	for (size_t i = 0; i < _activeCollider.size(); ++i)
	{
		OctTree::insert(_staticColliderTree, _activeCollider[i]);
	}

	for (size_t i = 0; i < _leafNodes.size(); ++i)
	{
		for (size_t j = 0; j < _leafNodes[i]->dynamicCollder.size(); ++j)
		{
			for (size_t x = 0; x < _leafNodes[i]->staticCollder.size(); ++x)
			{
				if (!_leafNodes[i]->dynamicCollder[j]->CheckCirlce(_leafNodes[i]->staticCollder[x])) continue;
				actualChecks++;
				if (_leafNodes[i]->dynamicCollder[j]->Check(_leafNodes[i]->staticCollder[x]))
				{
					_leafNodes[i]->dynamicCollder[j]->SetHit(true);
					_leafNodes[i]->staticCollder[x]->SetHit(true);
				}
			}
			for (size_t x = 0; x < _leafNodes[i]->dynamicCollder.size(); ++x)
			{
				if (x <= j)continue;
				if (!_leafNodes[i]->dynamicCollder[j]->CheckCirlce(_leafNodes[i]->dynamicCollder[x])) continue;
				actualChecks++;
				if (_leafNodes[i]->dynamicCollder[j]->Check(_leafNodes[i]->dynamicCollder[x]))
				{
					_leafNodes[i]->dynamicCollder[j]->SetHit(true);
					_leafNodes[i]->dynamicCollder[x]->SetHit(true);
				}
			}
		}

	}

	//for (size_t i = 0; i < _activeCollider.size(); i++)
	//{

	//	for (size_t j = 0; j < _activeCollider.size(); j++)
	//	{


	//		if (j <= i || !_activeCollider[i]->CheckCirlce(_activeCollider[j]))continue; //From 550.000 checks to ~1000

	//		actualChecks++;
	//		if (_activeCollider[i]->Check(_activeCollider[j]))
	//		{
	//			_activeCollider[i]->SetHit(true);
	//			_activeCollider[j]->SetHit(true);
	//			//HIT
	//		}
	//	}

	//	OctTree* senode = OctTree::getSmallestEnclosement(_staticColliderTree, _activeCollider[i]);
	//	std::vector<Collider*> closeCollider = OctTree::getPossiblyCollidingColliders(senode);

	//	for (size_t j = 0; j < closeCollider.size(); j++)
	//	{
	//		if (!_activeCollider[i]->CheckCirlce(closeCollider[j]))continue; //From 550.000 checks to ~1000

	//		actualChecks++;
	//		if (_activeCollider[i]->Check(closeCollider[j]))
	//		{
	//			_activeCollider[i]->SetHit(true);
	//			closeCollider[j]->SetHit(true);
	//			//HIT
	//		}
	//	}

	//}


	return actualChecks;



}