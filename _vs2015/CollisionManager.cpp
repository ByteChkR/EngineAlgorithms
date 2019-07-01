#include "CollisionManager.h"
#include "StaticOBBCollider.h"
#include "mge/core/GameObject.hpp"
#include "Debug.h"
#include "glm.hpp"
#include "QuadTree.h"
#include <vector>
#include "mge/core/AbstractGame.hpp"

std::vector<Collider*> CollisionManager::_activeCollider = std::vector<Collider*>();
std::vector<Collider*> CollisionManager::_passiveCollider = std::vector<Collider*>();
std::vector<OctTree*> CollisionManager::_leafNodes = std::vector<OctTree*>();
OctTree* CollisionManager::_staticColliderTree = nullptr;
CollisionManager* CollisionManager::instance = nullptr;
CollisionManager::CollisionManager()
{
	instance = this;
	_passiveCollider.reserve(7000);
	_activeCollider.reserve(3000);
	_staticColliderTree = OctTree::createTree();
	
}

CollisionManager::~CollisionManager()
{
	_activeCollider.clear();
	_passiveCollider.clear();
	_leafNodes.clear();
	delete _staticColliderTree;
	_staticColliderTree = nullptr;
}
int CollisionManager::actualChecks = 0;
int CollisionManager::CheckCollisions()
{


	actualChecks = 0;




	//for (size_t j = _leafNodes.size(); j--;)
	//{
	//	for (size_t i = _leafNodes[j]->dynamicCollder.size(); i--;)
	//	{
	//		if (OctTree::isEnclosing(_leafNodes[j]->point, _leafNodes[j]->extend, _leafNodes[j]->dynamicCollder[i]))
	//		{
	//			_leafNodes[j]->dynamicCollder[i]->SkipNext();
	//		}
	//		else
	//		{
	//			_leafNodes[j]->dynamicCollder.erase(_leafNodes[j]->dynamicCollder.begin() + i);
	//		}
	//	}

	//	if (_leafNodes[j]->ShouldRemove())
	//	{
	//		_leafNodes.erase(_leafNodes.begin() + j);
	//	}
	//	//Check if dynamic collider is still in leaf node.
	//	//if not push up the tree until it intersects. then go backwards into the tree again.
	//}

	for (size_t i = 0; i < _passiveCollider.size(); i++)
	{
		_passiveCollider[i]->SetHit(false);
	}

	if (AbstractGame::currentPreset->_enableOldDynamicRemoval)
	{
		for (size_t i = 0; i < _leafNodes.size(); i++)
		{
			_leafNodes[i]->dynamicCollder.clear();
		}
	}

	for (size_t i = _activeCollider.size(); i--;)
	{
		_activeCollider[i]->SetHit(false);
		if (AbstractGame::currentPreset->_enableOldDynamicRemoval || !_activeCollider[i]->ShouldSkip())
			OctTree::insert(_staticColliderTree, _activeCollider[i]);
	}

	for (size_t i = _leafNodes.size(); i--;)
	{
		if (AbstractGame::currentPreset->_enableNodeRemoval && _leafNodes[i]->ShouldRemove())
		{
			_leafNodes.erase(_leafNodes.begin() + i);
			continue;
		}
		for (size_t j = _leafNodes[i]->dynamicCollder.size(); j--;)
		{
			if (!AbstractGame::currentPreset->_enableOldDynamicRemoval)
			{
				if (OctTree::isEnclosing(_leafNodes[i]->point, _leafNodes[i]->extend, _leafNodes[i]->dynamicCollder[j]))
				{
					_leafNodes[i]->dynamicCollder[j]->SkipNext();
				}
				else
				{
					_leafNodes[i]->dynamicCollder.erase(_leafNodes[i]->dynamicCollder.begin() + j);
					continue;
				}
			}



			for (size_t x = _leafNodes[i]->staticCollder.size(); x--;)
			{
				if (AbstractGame::currentPreset->_enableCircleTest && !_leafNodes[i]->dynamicCollder[j]->CheckCirlce(_leafNodes[i]->staticCollder[x])) continue;
				actualChecks++;
				if (_leafNodes[i]->dynamicCollder[j]->Check(_leafNodes[i]->staticCollder[x]))
				{
					_leafNodes[i]->dynamicCollder[j]->SetHit(true);
					_leafNodes[i]->staticCollder[x]->SetHit(true);
				}
			}
			for (size_t x = _leafNodes[i]->dynamicCollder.size(); j+1 < x--;)
			{
				if ((AbstractGame::currentPreset->_enableCircleTest && !_leafNodes[i]->dynamicCollder[j]->CheckCirlce(_leafNodes[i]->dynamicCollder[x])))continue;
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