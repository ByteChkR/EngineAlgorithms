/**
	Purpose: Contains the logic of the Collision Algorithm

	@author Tim Akermann
*/

#include "mge/core/GameObject.hpp"
#include "CollisionManager.h"
#include "OBBCollider.h"
#include "OctTree.h"
#include <vector>
#include "mge/core/AbstractGame.hpp"


/**
	
	Purpose: Contains all active colliders for looping through the colliders fast. Allthough it could be faster if the list would be memory aligned.

	@author Tim Akermann
*/
std::vector<Collider*> CollisionManager::_activeCollider = std::vector<Collider*>();

/**

	Purpose: Contains all static colliders for looping through the colliders fast. Allthough it could be faster if the list would be memory aligned.

	@author Tim Akermann
*/
std::vector<Collider*> CollisionManager::_passiveCollider = std::vector<Collider*>();

/**

	Purpose: Contains all the leaf nodes for looping through the nodes fast. Allthough it could be faster if the list would be memory aligned.

	@author Tim Akermann
*/
std::vector<OctTree*> CollisionManager::_leafNodes = std::vector<OctTree*>();


/**

	Purpose: Root node of the octtree.

	@author Tim Akermann
*/
OctTree* CollisionManager::_staticColliderTree = nullptr;

/**

	Purpose: Singleton of the collision manager

	@author Tim Akermann
*/
CollisionManager* CollisionManager::instance = nullptr;


CollisionManager::CollisionManager()
{
	instance = this;
	//Reserve some space for the colliders. To add the colliders faster to the list.
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



/**

	Purpose: Implements the collision logic.

	@author Tim Akermann
*/
int CollisionManager::CheckCollisions() const
{


	actualChecks = 0;

	for (auto& i : _passiveCollider)
	{
		i->SetHit(false); //Reset the color of the cubes
	}

	if (AbstractGame::currentPreset->_enableOldDynamicRemoval)
	{
		for (auto& _leafNode : _leafNodes)
		{
			_leafNode->dynamicCollider.clear(); //Remove all dynamic colliders from the tree
		}
	}

	for (auto i = _activeCollider.size(); i--;)
	{
		_activeCollider[i]->SetHit(false); //Reset the color of the dynamic colliders
		if (AbstractGame::currentPreset->_enableOldDynamicRemoval || !_activeCollider[i]->ShouldSkip()) //If the for loop above removed all the colliders and the collider is not in the same node as before
			OctTree::insert(_staticColliderTree, _activeCollider[i]); //Add to the tree
	}

	for (auto i = _leafNodes.size(); i--;) //Loop through every leaf node
	{
		if (AbstractGame::currentPreset->_enableNodeRemoval && _leafNodes[i]->ShouldRemove()) //if node is empty remove it from leaf list.
		{
			_leafNodes.erase(_leafNodes.begin() + i);
			continue;
		}
		for (auto j = _leafNodes[i]->dynamicCollider.size(); j--;) 
		{
			if (!AbstractGame::currentPreset->_enableOldDynamicRemoval) 
			{
				if (OctTree::isEnclosing(_leafNodes[i]->point, _leafNodes[i]->extend, _leafNodes[i]->dynamicCollider[j])) // Check if the dynamic collider is still in the same node as before
				{
					_leafNodes[i]->dynamicCollider[j]->SkipNext(); //Do not readd the collider if it has not changed the node.
				}
				else
				{
					_leafNodes[i]->dynamicCollider.erase(_leafNodes[i]->dynamicCollider.begin() + j);//readd the node when it has changed the node.
					continue;
				}
			}



			for (auto x = _leafNodes[i]->staticCollider.size(); x--;) //Static vs Dynamic
			{
				if (AbstractGame::currentPreset->_enableCircleTest && !_leafNodes[i]->dynamicCollider[j]->CheckCirlce(_leafNodes[i]->staticCollider[x])) continue; //"Circle" Sphere Test will rule out most of the colliders
				actualChecks++; //The count of checks that went through the circle test and got resolved with the SAT algorithm
				if (_leafNodes[i]->dynamicCollider[j]->Check(_leafNodes[i]->staticCollider[x]))
				{
					_leafNodes[i]->dynamicCollider[j]->SetHit(true);
					_leafNodes[i]->staticCollider[x]->SetHit(true);
				}
			}
			for (auto x = _leafNodes[i]->dynamicCollider.size(); j+1 < x--;) //Dynamic vs Dynamic
			{
				if ((AbstractGame::currentPreset->_enableCircleTest && !_leafNodes[i]->dynamicCollider[j]->CheckCirlce(_leafNodes[i]->dynamicCollider[x])))continue; 
				actualChecks++;
				if (_leafNodes[i]->dynamicCollider[j]->Check(_leafNodes[i]->dynamicCollider[x]))
				{
					_leafNodes[i]->dynamicCollider[j]->SetHit(true);
					_leafNodes[i]->dynamicCollider[x]->SetHit(true);
				}
			}
		}

	}


	return actualChecks;



}
