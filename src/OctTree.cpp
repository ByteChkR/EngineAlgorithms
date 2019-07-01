#include "OctTree.h"
#include "CollisionManager.h"
#include "mge/core/AbstractGame.hpp"
const float OctTree::ROOT_RADIUS = glm::sqrt((float)ROOT_EXTENDS * ROOT_EXTENDS + ROOT_EXTENDS * ROOT_EXTENDS + ROOT_EXTENDS * ROOT_EXTENDS);
int OctTree::MAX_LEVEL = 0;


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
	ret->radius = glm::sqrt((float)ROOT_EXTENDS * ROOT_EXTENDS + ROOT_EXTENDS * ROOT_EXTENDS + ROOT_EXTENDS * ROOT_EXTENDS);;
	ret->root = nullptr;
	ret->removeFrame = REMOVAL_DELAY;
	ret->point = glm::vec3(512);
	ret->staticCollder = std::vector<Collider*>();
	ret->dynamicCollder = std::vector<Collider*>();
	ret->leftBackBot = ret->leftBackTop = ret->leftFrontBot = ret->leftFrontTop = ret->rightBackBot = ret->rightBackTop = ret->rightFrontBot = ret->rightFrontTop = nullptr;
	ret->octant = Octants::LEFTBACKBOT;
	if (0 == MAX_LEVEL)
	{
		ret->staticCollder.reserve(10);
		ret->dynamicCollder.reserve(10);
		CollisionManager::_leafNodes.push_back(ret);
	}
	return ret;
}

OctTree* OctTree::createNode(OctTree* root, Octants octant, unsigned int depth)
{
	OctTree* ret = new OctTree;
	ret->extend = root->extend / 2;
	ret->radius = ret->extend*ret->extend;
	ret->radius = glm::fastSqrt(ret->radius + ret->radius + ret->radius);
	ret->root = root;
	ret->point = getChildPosition(root, octant, ret->extend);
	ret->staticCollder = std::vector<Collider*>();
	ret->octant = octant;
	ret->dynamicCollder = std::vector<Collider*>();
	ret->removeFrame = REMOVAL_DELAY;
	ret->leftBackBot = ret->leftBackTop = ret->leftFrontBot = ret->leftFrontTop = ret->rightBackBot = ret->rightBackTop = ret->rightFrontBot = ret->rightFrontTop = nullptr;
	if (depth == MAX_LEVEL)
	{
		ret->staticCollder.reserve(10);
		ret->dynamicCollder.reserve(10);
		CollisionManager::_leafNodes.push_back(ret);
	}
	return ret;
}


void OctTree::insert(OctTree* root, Collider* object, unsigned int depth)
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

//OctTree* OctTree::getSmallestEnclosement(OctTree* root, Collider* object)
//{
//	return getSmallestEnclosement(root, object, 0);
//}

//OctTree* OctTree::getSmallestEnclosement(OctTree* root, Collider* object, unsigned int depth)
//{
//	if (root == nullptr)
//	{
//		return nullptr;
//	}
//
//	if (depth == MAX_LEVEL)
//	{
//		//root->add(object);
//		return root;
//	}
//
//	bool checkedbranchisnullpointer = false;
//
//	if (((checkedbranchisnullpointer = root->rightBackBot == nullptr) && isEnclosingChild(root, Octants::RIGHTBACKBOT, object)) || (!checkedbranchisnullpointer&& isEnclosing(root->rightBackBot, object)))
//	{
//		if (checkedbranchisnullpointer)return root;
//		return getSmallestEnclosement(root->rightBackBot, object, depth + 1);
//	}
//	if (((checkedbranchisnullpointer = root->rightBackTop == nullptr) && isEnclosingChild(root, Octants::RIGHTBACKTOP, object)) || (!checkedbranchisnullpointer&& isEnclosing(root->rightBackTop, object)))
//	{
//		if (checkedbranchisnullpointer)return root;
//		return getSmallestEnclosement(root->rightBackTop, object, depth + 1);
//	}
//	if (((checkedbranchisnullpointer = root->rightFrontBot == nullptr) && isEnclosingChild(root, Octants::RIGHTFRONTBOT, object)) || (!checkedbranchisnullpointer&& isEnclosing(root->rightFrontBot, object)))
//	{
//		if (checkedbranchisnullpointer)return root;
//		return getSmallestEnclosement(root->rightFrontBot, object, depth + 1);
//	}
//	if (((checkedbranchisnullpointer = root->rightFrontTop == nullptr) && isEnclosingChild(root, Octants::RIGHTFRONTTOP, object)) || (!checkedbranchisnullpointer&& isEnclosing(root->rightFrontTop, object)))
//	{
//		if (checkedbranchisnullpointer)return root;
//		return getSmallestEnclosement(root->rightFrontTop, object, depth + 1);
//	}
//	if (((checkedbranchisnullpointer = root->leftBackBot == nullptr) && isEnclosingChild(root, Octants::LEFTBACKBOT, object)) || (!checkedbranchisnullpointer&& isEnclosing(root->leftBackBot, object)))
//	{
//		if (checkedbranchisnullpointer)return root;
//		return getSmallestEnclosement(root->leftBackBot, object, depth + 1);
//	}
//	if (((checkedbranchisnullpointer = root->leftBackTop == nullptr) && isEnclosingChild(root, Octants::LEFTBACKTOP, object)) || (!checkedbranchisnullpointer&& isEnclosing(root->leftBackTop, object)))
//	{
//		if (checkedbranchisnullpointer)return root;
//		return getSmallestEnclosement(root->leftBackTop, object, depth + 1);
//	}
//	if (((checkedbranchisnullpointer = root->leftFrontBot == nullptr) && isEnclosingChild(root, Octants::LEFTFRONTBOT, object)) || (!checkedbranchisnullpointer&& isEnclosing(root->leftFrontBot, object)))
//	{
//		if (checkedbranchisnullpointer)return root;
//		return getSmallestEnclosement(root->leftFrontBot, object, depth + 1);
//	}
//	if (((checkedbranchisnullpointer = root->leftFrontTop == nullptr) && isEnclosingChild(root, Octants::LEFTFRONTTOP, object)) || (!checkedbranchisnullpointer&& isEnclosing(root->leftFrontTop, object)))
//	{
//		if (checkedbranchisnullpointer)return root;
//		return getSmallestEnclosement(root->leftFrontTop, object, depth + 1);
//	}
//	return root;
//}

void OctTree::ResetColliderHit(OctTree* root)
{
	if (root == nullptr) return;
	for (size_t i = 0; i < root->staticCollder.size(); ++i)
	{
		root->staticCollder[i]->SetHit(false);

	}


}
//
//std::vector<Collider*> OctTree::getPossiblyCollidingColliders(OctTree* containingNode)
//{
//	std::vector<Collider*> ret = std::vector<Collider*>();
//	ret.insert(ret.end(), containingNode->staticCollder.begin(), containingNode->staticCollder.end());
//	ret.insert(ret.end(), containingNode->dynamicCollder.begin(), containingNode->dynamicCollder.end());
//	if (containingNode->root == nullptr)return ret;
//	std::vector<Collider*> parentColliders = getPossiblyCollidingColliders(containingNode->root);
//	ret.insert(ret.end(), parentColliders.begin(), parentColliders.end());
//
//	return ret;
//
//}

void OctTree::insert(OctTree* root, Collider* object)
{
	insert(root, object, 0);
}

//bool OctTree::isEnclosing(OctTree* root, Collider* object)
//{
//
//	return isEnclosing(root->point, root->extend, object);
//
//}
//
bool OctTree::isEnclosing(glm::vec3 rootpoint, float rootextend, Collider* object)
{
	glm::vec3 pos = object->GetOwner()->getLocalPosition();
	if (rootpoint.x + rootextend < pos.x + object->GetRadius())return false;
	if (rootpoint.x - rootextend > pos.x - object->GetRadius())return false;
	if (rootpoint.y + rootextend < pos.y + object->GetRadius())return false;
	if (rootpoint.y - rootextend > pos.y - object->GetRadius())return false;
	if (rootpoint.z + rootextend < pos.z + object->GetRadius())return false;
	if (rootpoint.z - rootextend > pos.z - object->GetRadius())return false;

	return true;
}
//
//
//
//bool OctTree::isEnclosingChild(OctTree* root, Octants octant, Collider* object)
//{
//	float extends = root->extend / 2;
//	glm::vec3 position = getChildPosition(root, octant);
//
//	return isEnclosing(position, extends, object);
//
//}

bool OctTree::isIntersecting(OctTree* root, Collider* object)
{

	return isIntersecting(root->point, root->extend, object);
}

bool OctTree::isIntersectingChild(OctTree* root, Octants octant, Collider* object)
{
	float extends = root->extend / 2;
	glm::vec3 position = getChildPosition(root, octant, extends);
	return isIntersecting(position, extends, object);
}

bool OctTree::isIntersecting(glm::vec3 rootpoint, float rootextend, Collider* object)
{
	if (rootpoint.x + rootextend < object->GetOwner()->getLocalPosition().x - object->GetRadius() || rootpoint.x - rootextend > object->GetOwner()->getLocalPosition().x + object->GetRadius() ||
		rootpoint.y + rootextend < object->GetOwner()->getLocalPosition().y - object->GetRadius() || rootpoint.y - rootextend > object->GetOwner()->getLocalPosition().y + object->GetRadius() ||
		rootpoint.z + rootextend < object->GetOwner()->getLocalPosition().z - object->GetRadius() || rootpoint.z - rootextend > object->GetOwner()->getLocalPosition().z + object->GetRadius())
		return false;

	return true;
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


glm::vec3 OctTree::getChildPosition(OctTree* root, Octants octant, float extend)
{
	/*glm::vec3 pos = root->point;
	switch (octant)
	{
	case LEFTBACKTOP:
		pos += glm::vec3(-1, 1, -1)*glm::vec3(extend);
		break;
	case LEFTFRONTTOP:
		pos += glm::vec3(-1, 1, 1)*glm::vec3(extend);
		break;
	case LEFTBACKBOT:
		pos += glm::vec3(-1, -1, -1)*glm::vec3(extend);
		break;
	case LEFTFRONTBOT:
		pos += glm::vec3(-1, 1, 1)*glm::vec3(extend);
		break;
	case RIGHTBACKTOP:
		pos += glm::vec3(1, 1, -1)*glm::vec3(extend);
		break;
	case RIGHTFRONTTOP:
		pos += glm::vec3(1, 1, 1)*glm::vec3(extend);
		break;
	case RIGHTBACKBOT:
		pos += glm::vec3(1, -1, -1)*glm::vec3(extend);
		break;
	case RIGHTFRONTBOT:
		pos += glm::vec3(1, -1, 1)*glm::vec3(extend);
		break;
	default:
		break;
	}
	return pos; */
	glm::vec3 ret;
	ret.x = root->point.x + octants[octant].x * extend;
	ret.y = root->point.y + octants[octant].y * extend;
	ret.z = root->point.z + octants[octant].z * extend;
	return ret;
}

void OctTree::add(Collider* object)
{
	if ((staticCollder.size() == 0 || dynamicCollder.size() == 0) && removeFrame <= 0)
		CollisionManager::_leafNodes.push_back(this);
	if (object->IsStatic())
		staticCollder.push_back(object);
	else
		dynamicCollder.push_back(object);

}

bool OctTree::ShouldRemove()
{
	if (staticCollder.size() == 0 && dynamicCollder.size() == 0)
		removeFrame--;
	else
		removeFrame = REMOVAL_DELAY;
	if (removeFrame <= 0)
	{
		return true;
	}
	return false;
}
