#include "QuadTree.h"

const float OctTree::ROOT_RADIUS = glm::sqrt(ROOT_EXTENDS * ROOT_EXTENDS + ROOT_EXTENDS * ROOT_EXTENDS + ROOT_EXTENDS * ROOT_EXTENDS);

OctTree* OctTree::createTree()
{
	OctTree* ret = new OctTree;
	ret->extend = ROOT_EXTENDS;
	ret->radius = glm::sqrt(ROOT_EXTENDS * ROOT_EXTENDS + ROOT_EXTENDS * ROOT_EXTENDS + ROOT_EXTENDS * ROOT_EXTENDS);;
	ret->root = nullptr;
	ret->point = glm::vec3(512);
	ret->collder = std::vector<Collider*>();
	ret->leftBackBot = ret->leftBackTop = ret->leftFrontBot = ret->leftFrontTop = ret->rightBackBot = ret->rightBackTop = ret->rightFrontBot = ret->rightFrontTop = nullptr;
	return ret;
}

OctTree* OctTree::createNode(OctTree* root, Octants octant)
{
	OctTree* ret = new OctTree;
	ret->extend = root->extend / 2;
	ret->radius = glm::sqrt(ret->extend * ret->extend + ret->extend * ret->extend + ret->extend * ret->extend);;
	ret->root = root;
	glm::vec3 pos = getChildPosition(root, octant);
	ret->point = pos;
	ret->collder = std::vector<Collider*>();
	ret->leftBackBot = ret->leftBackTop = ret->leftFrontBot = ret->leftFrontTop = ret->rightBackBot = ret->rightBackTop = ret->rightFrontBot = ret->rightFrontTop = nullptr;
	return ret;
}


OctTree* OctTree::insert(OctTree* root, Collider* object, unsigned int depth)
{
	if (root == nullptr)
	{
		return nullptr;
	}

	if (depth == MAX_LEVEL)
	{
		root->add(object);
		return root;
	}

	bool checkedbranchisnullpointer = false;

	if (((checkedbranchisnullpointer = root->rightBackBot == nullptr) && isEnclosingChild(root, Octants::RIGHTBACKBOT, object)) || (!checkedbranchisnullpointer&& isEnclosing(root->rightBackBot, object)))
	{
		if (checkedbranchisnullpointer)root->rightBackBot = createNode(root, Octants::RIGHTBACKBOT);
		insert(root->rightBackBot, object, depth + 1);
	}
	if (((checkedbranchisnullpointer = root->rightBackTop == nullptr) && isEnclosingChild(root, Octants::RIGHTBACKTOP, object)) || (!checkedbranchisnullpointer&& isEnclosing(root->rightBackTop, object)))
	{
		if (checkedbranchisnullpointer)root->rightBackTop = createNode(root, Octants::RIGHTBACKTOP);
		insert(root->rightBackTop, object, depth + 1);
	}
	if (((checkedbranchisnullpointer = root->rightFrontBot == nullptr) && isEnclosingChild(root, Octants::RIGHTFRONTBOT, object)) || (!checkedbranchisnullpointer&&  isEnclosing(root->rightFrontBot, object)))
	{
		if (checkedbranchisnullpointer)root->rightFrontBot = createNode(root, Octants::RIGHTFRONTBOT);
		insert(root->rightFrontBot, object, depth + 1);
	}
	if (((checkedbranchisnullpointer = root->rightFrontTop == nullptr) && isEnclosingChild(root, Octants::RIGHTFRONTTOP, object)) || (!checkedbranchisnullpointer&& isEnclosing(root->rightFrontTop, object)))
	{
		if (checkedbranchisnullpointer)root->rightFrontTop = createNode(root, Octants::RIGHTFRONTTOP);
		insert(root->rightFrontTop, object, depth + 1);
	}
	if (((checkedbranchisnullpointer = root->leftBackBot == nullptr) && isEnclosingChild(root, Octants::LEFTBACKBOT, object)) || (!checkedbranchisnullpointer&& isEnclosing(root->leftBackBot, object)))
	{
		if (checkedbranchisnullpointer)root->leftBackBot = createNode(root, Octants::LEFTBACKBOT);
		insert(root->leftBackBot, object, depth + 1);
	}
	if (((checkedbranchisnullpointer = root->leftBackTop == nullptr) && isEnclosingChild(root, Octants::LEFTBACKTOP, object)) || (!checkedbranchisnullpointer&& isEnclosing(root->leftBackTop, object)))
	{
		if (checkedbranchisnullpointer)root->leftBackTop = createNode(root, Octants::LEFTBACKTOP);
		insert(root->leftBackTop, object, depth + 1);
	}
	if (((checkedbranchisnullpointer = root->leftFrontBot == nullptr) && isEnclosingChild(root, Octants::LEFTFRONTBOT, object)) || (!checkedbranchisnullpointer&& isEnclosing(root->leftFrontBot, object)))
	{
		if (checkedbranchisnullpointer)root->leftFrontBot = createNode(root, Octants::LEFTFRONTBOT);
		insert(root->leftFrontBot, object, depth + 1);
	}
	if (((checkedbranchisnullpointer = root->leftFrontTop == nullptr) && isEnclosingChild(root, Octants::LEFTFRONTTOP, object)) || (!checkedbranchisnullpointer&& isEnclosing(root->leftFrontTop, object)))
	{
		if (checkedbranchisnullpointer)root->leftFrontTop = createNode(root, Octants::LEFTFRONTTOP);
		insert(root->leftFrontTop, object, depth + 1);
	}


	//root->add(object);
	return root;
}

OctTree* OctTree::getSmallestEnclosement(OctTree* root, Collider* object)
{
	return getSmallestEnclosement(root, object, 0);
}

OctTree* OctTree::getSmallestEnclosement(OctTree* root, Collider* object, unsigned int depth)
{
	if (root == nullptr)
	{
		return nullptr;
	}

	if (depth == MAX_LEVEL)
	{
		//root->add(object);
		return root;
	}

	bool checkedbranchisnullpointer = false;

	if (((checkedbranchisnullpointer = root->rightBackBot == nullptr) && isEnclosingChild(root, Octants::RIGHTBACKBOT, object)) || (!checkedbranchisnullpointer&& isEnclosing(root->rightBackBot, object)))
	{
		if (checkedbranchisnullpointer)return root;
		return getSmallestEnclosement(root->rightBackBot, object, depth + 1);
	}
	if (((checkedbranchisnullpointer = root->rightBackTop == nullptr) && isEnclosingChild(root, Octants::RIGHTBACKTOP, object)) || (!checkedbranchisnullpointer&& isEnclosing(root->rightBackTop, object)))
	{
		if (checkedbranchisnullpointer)return root;
		return getSmallestEnclosement(root->rightBackTop, object, depth + 1);
	}
	if (((checkedbranchisnullpointer = root->rightFrontBot == nullptr) && isEnclosingChild(root, Octants::RIGHTFRONTBOT, object)) || (!checkedbranchisnullpointer&& isEnclosing(root->rightFrontBot, object)))
	{
		if (checkedbranchisnullpointer)return root;
		return getSmallestEnclosement(root->rightFrontBot, object, depth + 1);
	}
	if (((checkedbranchisnullpointer = root->rightFrontTop == nullptr) && isEnclosingChild(root, Octants::RIGHTFRONTTOP, object)) || (!checkedbranchisnullpointer&& isEnclosing(root->rightFrontTop, object)))
	{
		if (checkedbranchisnullpointer)return root;
		return getSmallestEnclosement(root->rightFrontTop, object, depth + 1);
	}
	if (((checkedbranchisnullpointer = root->leftBackBot == nullptr) && isEnclosingChild(root, Octants::LEFTBACKBOT, object)) || (!checkedbranchisnullpointer&& isEnclosing(root->leftBackBot, object)))
	{
		if (checkedbranchisnullpointer)return root;
		return getSmallestEnclosement(root->leftBackBot, object, depth + 1);
	}
	if (((checkedbranchisnullpointer = root->leftBackTop == nullptr) && isEnclosingChild(root, Octants::LEFTBACKTOP, object)) || (!checkedbranchisnullpointer&& isEnclosing(root->leftBackTop, object)))
	{
		if (checkedbranchisnullpointer)return root;
		return getSmallestEnclosement(root->leftBackTop, object, depth + 1);
	}
	if (((checkedbranchisnullpointer = root->leftFrontBot == nullptr) && isEnclosingChild(root, Octants::LEFTFRONTBOT, object)) || (!checkedbranchisnullpointer&& isEnclosing(root->leftFrontBot, object)))
	{
		if (checkedbranchisnullpointer)return root;
		return getSmallestEnclosement(root->leftFrontBot, object, depth + 1);
	}
	if (((checkedbranchisnullpointer = root->leftFrontTop == nullptr) && isEnclosingChild(root, Octants::LEFTFRONTTOP, object)) || (!checkedbranchisnullpointer&& isEnclosing(root->leftFrontTop, object)))
	{
		if (checkedbranchisnullpointer)return root;
		return getSmallestEnclosement(root->leftFrontTop, object, depth + 1);
	}
	return root;
}

void OctTree::ResetColliderHit(OctTree* root)
{
	if (root == nullptr) return;
	for (size_t i = 0; i < root->collder.size(); i++)
	{
		root->collder[i]->SetHit(false);
	}

	OctTree::ResetColliderHit(root->leftBackBot);
	OctTree::ResetColliderHit(root->leftFrontBot);
	OctTree::ResetColliderHit(root->leftBackTop);
	OctTree::ResetColliderHit(root->leftFrontTop);
	OctTree::ResetColliderHit(root->rightBackBot);
	OctTree::ResetColliderHit(root->rightFrontBot);
	OctTree::ResetColliderHit(root->rightBackTop);
	OctTree::ResetColliderHit(root->rightFrontTop);

}

std::vector<Collider*> OctTree::getPossiblyCollidingColliders(OctTree* containingNode)
{
	std::vector<Collider*> ret = std::vector<Collider*>();
	ret.insert(ret.end(), containingNode->collder.begin(), containingNode->collder.end());
	if (containingNode->root == nullptr)return ret;
	std::vector<Collider*> parentColliders = getPossiblyCollidingColliders(containingNode->root);
	ret.insert(ret.end(), parentColliders.begin(), parentColliders.end());

	return ret;

}

OctTree* OctTree::insert(OctTree* root, Collider* object)
{
	return insert(root, object, 0);
}

bool OctTree::isEnclosing(OctTree* root, Collider* object)
{

	return isEnclosing(root->point, root->extend, object);

}

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

bool OctTree::isIntersecting(glm::vec3 rootpoint, float rootextend, Collider* object)
{
	glm::vec3 pos = object->GetOwner()->getLocalPosition();
	if (rootpoint.x + rootextend < pos.x - object->GetRadius() || rootpoint.x - rootextend > pos.x + object->GetRadius())return false;
	if (rootpoint.y + rootextend < pos.y - object->GetRadius() || rootpoint.y - rootextend > pos.y + object->GetRadius())return false;
	if (rootpoint.z + rootextend < pos.z - object->GetRadius() || rootpoint.z - rootextend > pos.z + object->GetRadius())return false;

	return true;
}

bool OctTree::isEnclosingChild(OctTree* root, Octants octant, Collider* object)
{
	float extends = root->extend / 2;
	glm::vec3 position = getChildPosition(root, octant);

	return isEnclosing(position, extends, object);

}


glm::vec3 OctTree::getChildPosition(OctTree* root, Octants octant)
{
	float offset = root->extend / 2;
	float extend = root->extend / 2;
	glm::vec3 pos = root->point;
	switch (octant)
	{
	case LEFTBACKTOP:
		pos += glm::vec3(-1, 1, -1)*glm::vec3(offset);
		break;
	case LEFTFRONTTOP:
		pos += glm::vec3(-1, 1, 1)*glm::vec3(offset);
		break;
	case LEFTBACKBOT:
		pos += glm::vec3(-1, -1, -1)*glm::vec3(offset);
		break;
	case LEFTFRONTBOT:
		pos += glm::vec3(-1, 1, 1)*glm::vec3(offset);
		break;
	case RIGHTBACKTOP:
		pos += glm::vec3(1, 1, -1)*glm::vec3(offset);
		break;
	case RIGHTFRONTTOP:
		pos += glm::vec3(1, 1, 1)*glm::vec3(offset);
		break;
	case RIGHTBACKBOT:
		pos += glm::vec3(1, -1, -1)*glm::vec3(offset);
		break;
	case RIGHTFRONTBOT:
		pos += glm::vec3(1, -1, 1)*glm::vec3(offset);
		break;
	default:
		break;
	}
	return pos;
}

void OctTree::add(Collider* object)
{
	//store x/y/z distance to bounds of this tree in + and - directions
	//store world position
	collder.push_back(object);
}