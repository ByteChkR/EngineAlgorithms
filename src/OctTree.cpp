/**
	Purpose: Contains the implementation of the OctTree.

	@author Tim Akermann
*/
#include "OctTree.h"
#include "CollisionManager.h"
#include "mge/core/AbstractGame.hpp"
const float OctTree::ROOT_RADIUS = glm::sqrt(static_cast<float>(ROOT_EXTENDS) * ROOT_EXTENDS + ROOT_EXTENDS * ROOT_EXTENDS + ROOT_EXTENDS * ROOT_EXTENDS);
unsigned int OctTree::MAX_LEVEL = 0;


OctTree::~OctTree()
{
	delete leftBackBot;
	delete leftBackTop;
	delete leftFrontBot;
	delete leftFrontTop;
	delete rightBackBot;
	delete rightBackTop;
	delete rightFrontBot;
	delete rightFrontTop;
}


OctTree* OctTree::createTree()
{
	OctTree* ret = new OctTree;
	MAX_LEVEL = AbstractGame::currentPreset->_treeDepth;
	ret->extend = ROOT_EXTENDS;
	ret->radius = glm::sqrt(static_cast<float>(ROOT_EXTENDS) * ROOT_EXTENDS + ROOT_EXTENDS * ROOT_EXTENDS + ROOT_EXTENDS * ROOT_EXTENDS);;
	ret->root = nullptr;
	ret->removeFrame = REMOVAL_DELAY;
	ret->point = glm::vec3(512);
	ret->staticCollider = std::vector<Collider*>();
	ret->dynamicCollider = std::vector<Collider*>();
	ret->leftBackBot = ret->leftBackTop = ret->leftFrontBot = ret->leftFrontTop = ret->rightBackBot = ret->rightBackTop = ret->rightFrontBot = ret->rightFrontTop = nullptr;
	ret->octant = Octants::LEFTBACKBOT;
	if (0 == MAX_LEVEL)
	{
		ret->staticCollider.reserve(10);
		ret->dynamicCollider.reserve(10);
		CollisionManager::_leafNodes.push_back(ret);
	}
	return ret;
}

OctTree* OctTree::createNode(OctTree* root, const Octants octant, const unsigned int depth)
{
	OctTree* ret = new OctTree;
	ret->extend = root->extend / 2;
	ret->radius = ret->extend*ret->extend;
	ret->radius = glm::fastSqrt(ret->radius + ret->radius + ret->radius);
	ret->root = root;
	ret->point = getChildPosition(root, octant, ret->extend);
	ret->staticCollider = std::vector<Collider*>();
	ret->octant = octant;
	ret->dynamicCollider = std::vector<Collider*>();
	ret->removeFrame = REMOVAL_DELAY;
	ret->leftBackBot = ret->leftBackTop = ret->leftFrontBot = ret->leftFrontTop = ret->rightBackBot = ret->rightBackTop = ret->rightFrontBot = ret->rightFrontTop = nullptr;
	if (depth == MAX_LEVEL)
	{
		ret->staticCollider.reserve(10);
		ret->dynamicCollider.reserve(10);
		CollisionManager::_leafNodes.push_back(ret);
	}
	return ret;
}


void OctTree::insert(OctTree* root, Collider* object, const unsigned int depth)
{

	if (depth == MAX_LEVEL)
	{
		root->add(object);
		return;
	}

	if (root->rightBackBot == nullptr && isIntersectingChild(root, Octants::RIGHTBACKBOT, object))
	{
		root->rightBackBot = createNode(root, Octants::RIGHTBACKBOT, depth + 1);
		insert(root->rightBackBot, object, depth + 1);
	}
	else if (root->rightBackBot != nullptr && isIntersecting(root->rightBackBot, object))
	{
		insert(root->rightBackBot, object, depth + 1);
	}

	if (root->rightBackTop == nullptr)
	{
		if (isIntersectingChild(root, Octants::RIGHTBACKTOP, object))
		{
			root->rightBackTop = createNode(root, Octants::RIGHTBACKTOP, depth + 1);
			insert(root->rightBackTop, object, depth + 1);
		}
	}
	else
	{
		if (isIntersecting(root->rightBackTop, object))
			insert(root->rightBackTop, object, depth + 1);
	}

	if (root->rightFrontBot == nullptr)
	{
		if (isIntersectingChild(root, Octants::RIGHTFRONTBOT, object))
		{
			root->rightFrontBot = createNode(root, Octants::RIGHTFRONTBOT, depth + 1);
			insert(root->rightFrontBot, object, depth + 1);
		}
	}
	else
	{
		if (isIntersecting(root->rightFrontBot, object))
			insert(root->rightFrontBot, object, depth + 1);
	}

	if (root->rightFrontTop == nullptr)
	{
		if (isIntersectingChild(root, Octants::RIGHTFRONTTOP, object))
		{
			root->rightFrontTop = createNode(root, Octants::RIGHTFRONTTOP, depth + 1);
			insert(root->rightFrontTop, object, depth + 1);
		}
	}
	else
	{
		if (isIntersecting(root->rightFrontTop, object))
			insert(root->rightFrontTop, object, depth + 1);
	}


	if (root->leftBackBot == nullptr)
	{
		if (isIntersectingChild(root, Octants::LEFTBACKBOT, object))
		{
			root->leftBackBot = createNode(root, Octants::LEFTBACKBOT, depth + 1);
			insert(root->leftBackBot, object, depth + 1);
		}
	}
	else
	{
		if (isIntersecting(root->leftBackBot, object))
			insert(root->leftBackBot, object, depth + 1);
	}


	if (root->leftBackTop == nullptr)
	{
		if (isIntersectingChild(root, Octants::LEFTBACKTOP, object))
		{
			root->leftBackTop = createNode(root, Octants::LEFTBACKTOP, depth + 1);
			insert(root->leftBackTop, object, depth + 1);
		}
	}
	else
	{
		if (isIntersecting(root->leftBackTop, object))
			insert(root->leftBackTop, object, depth + 1);
	}

	if (root->leftFrontBot == nullptr)
	{
		if (isIntersectingChild(root, Octants::LEFTFRONTBOT, object))
		{
			root->leftFrontBot = createNode(root, Octants::LEFTFRONTBOT, depth + 1);
			insert(root->leftFrontBot, object, depth + 1);
		}
	}
	else
	{
		if (isIntersecting(root->leftFrontBot, object))
			insert(root->leftFrontBot, object, depth + 1);
	}


	if (root->leftFrontTop == nullptr)
	{
		if (isIntersectingChild(root, Octants::LEFTFRONTTOP, object))
		{
			root->leftFrontTop = createNode(root, Octants::LEFTFRONTTOP, depth + 1);
			insert(root->leftFrontTop, object, depth + 1);
		}
	}
	else
	{
		if (isIntersecting(root->leftFrontTop, object))
			insert(root->leftFrontTop, object, depth + 1);
	}


	//root->add(object);
	return;
}



void OctTree::ResetColliderHit(OctTree* root)
{
	if (root == nullptr) return;
	for (auto& i : root->staticCollider)
	{
		i->SetHit(false);

	}


}

void OctTree::insert(OctTree* root, Collider* object)
{
	insert(root, object, 0);
}

bool OctTree::isEnclosing(glm::vec3 rootpoint, float rootextend, Collider* object)
{
	const glm::vec3 pos = object->GetOwner()->getLocalPosition();
	if (rootpoint.x + rootextend < pos.x + object->GetRadius())return false;
	if (rootpoint.x - rootextend > pos.x - object->GetRadius())return false;
	if (rootpoint.y + rootextend < pos.y + object->GetRadius())return false;
	if (rootpoint.y - rootextend > pos.y - object->GetRadius())return false;
	if (rootpoint.z + rootextend < pos.z + object->GetRadius())return false;
	if (rootpoint.z - rootextend > pos.z - object->GetRadius())return false;

	return true;
}

bool OctTree::isIntersecting(OctTree* root, Collider* object)
{

	return isIntersecting(root->point, root->extend, object);
}

bool OctTree::isIntersectingChild(OctTree* root, const Octants octant, Collider* object)
{
	const float extends = root->extend / 2;
	const glm::vec3 position = getChildPosition(root, octant, extends);
	return isIntersecting(position, extends, object);
}




bool OctTree::isIntersecting(const glm::vec3 rootpoint, const float rootextend, Collider* object)
{
	return !(rootpoint.x + rootextend < object->GetOwner()->getLocalPosition().x - object->GetRadius() || rootpoint.x -
		rootextend > object->GetOwner()->getLocalPosition().x + object->GetRadius() || rootpoint.y + rootextend < object
		                                                                                                          ->
		                                                                                                          GetOwner()
		                                                                                                          ->
		                                                                                                          getLocalPosition()
		                                                                                                          .y -
		object->GetRadius() || rootpoint.y - rootextend > object->GetOwner()->getLocalPosition().y + object->GetRadius()
		|| rootpoint.z + rootextend < object->GetOwner()->getLocalPosition().z - object->GetRadius() || rootpoint.z -
		rootextend > object->GetOwner()->getLocalPosition().z + object->GetRadius());
}


static glm::vec3 octants[8]
{

	glm::vec3(-1,1,-1),
	glm::vec3(-1,1,1),
	glm::vec3(-1,-1,-1),
	glm::vec3(-1, 1, 1),
	glm::vec3(1, 1, -1),
	glm::vec3(1, 1, 1),
	glm::vec3(1, -1, -1),
	glm::vec3(1, -1, 1)
};


glm::vec3 OctTree::getChildPosition(OctTree* root, Octants octant, const float extend)
{
	glm::vec3 ret;
	ret.x = root->point.x + octants[octant].x * extend;
	ret.y = root->point.y + octants[octant].y * extend;
	ret.z = root->point.z + octants[octant].z * extend;
	return ret;
}

void OctTree::add(Collider* object)
{
	if ((staticCollider.empty() || dynamicCollider.empty()) && removeFrame <= 0)
		CollisionManager::_leafNodes.push_back(this);
	if (object->IsStatic())
		staticCollider.push_back(object);
	else
		dynamicCollider.push_back(object);

}

bool OctTree::ShouldRemove()
{
	if (staticCollider.empty() && dynamicCollider.empty())
		removeFrame--;
	else
		removeFrame = REMOVAL_DELAY;
	return removeFrame <= 0;
}
