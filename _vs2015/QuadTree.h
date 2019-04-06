#ifndef QUADTREE_HPP


#define QUADTREE_HPP

#include "glm.hpp"
#include <vector>
#include "StaticOBBCollider.h"

enum Octants
{
	LEFTBACKTOP, LEFTFRONTTOP, LEFTBACKBOT, LEFTFRONTBOT,
	RIGHTBACKTOP, RIGHTFRONTTOP, RIGHTBACKBOT, RIGHTFRONTBOT
};

struct OctTree
{
public:
	static const int MAX_LEVEL = 10;
	static const int ROOT_EXTENDS = 1024;
	static const float ROOT_RADIUS;
	OctTree *leftBackTop, *leftFrontTop,
		*rightBackTop, *rightFrontTop,
		*leftBackBot, *leftFrontBot,
		*rightBackBot, *rightFrontBot,
		*root;

	float extend, radius;
	glm::vec3 point;
	std::vector<Collider*> collder;
	static OctTree* createTree();
	static OctTree* createNode(OctTree* root, Octants octant);
	static OctTree* insert(OctTree* root, Collider* object, unsigned int depth);
	static OctTree* insert(OctTree* root, Collider* object);
	static OctTree* remove(OctTree* root, Collider* object);
	static OctTree* update(OctTree* root);
	static bool isEnclosing(OctTree* root, Collider* object);
	static bool isEnclosingChild(OctTree* root, Octants octant, Collider* collider);
	static glm::vec3 getChildPosition(OctTree* root, Octants octant);
	static bool isEnclosing(glm::vec3 rootPosiion, float rootExtend, Collider* collider);
	static bool isIntersecting(glm::vec3 rootPosiion, float rootExtend, Collider* collider);
	void add(Collider* collider);
	static OctTree* getSmallestEnclosement(OctTree* root, Collider* collider, unsigned int depth);
	static OctTree* getSmallestEnclosement(OctTree* root, Collider* collider);
	static std::vector<Collider*> getPossiblyCollidingColliders(OctTree* containingNode);
	static void ResetColliderHit(OctTree* root);
};


#endif // !QUADTREE_HPP
