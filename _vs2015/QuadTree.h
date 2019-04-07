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
	static const int MAX_LEVEL = 4;
	static const int ROOT_EXTENDS = 512;
	static const float ROOT_RADIUS;
	OctTree *leftBackTop, *leftFrontTop,
		*rightBackTop, *rightFrontTop,
		*leftBackBot, *leftFrontBot,
		*rightBackBot, *rightFrontBot,
		*root;

	float extend, radius;
	static int addedcoint;
	glm::vec3 point;
	std::vector<Collider*> dynamicCollder;
	std::vector<Collider*> staticCollder;
	static OctTree* createTree();
	static OctTree* createNode(OctTree* root, Octants octant, unsigned int depth);
	static void insert(OctTree* root, Collider* object, unsigned int depth);
	static void insert(OctTree* root, Collider* object);

	static glm::vec3 getChildPosition(OctTree* root, Octants octant, float extend);

	static bool isIntersecting(OctTree* root, Collider* object);
	static bool isIntersectingChild(OctTree* root, Octants octant, Collider* object);
	static bool isIntersecting(glm::vec3 rootPosiion, float rootExtend, Collider* collider);
	void add(Collider* collider);
	void updateDynamics();
	void updateDynamic(Collider* object);
	static bool isEnclosing(glm::vec3 rootpoint, float rootextend, Collider* object);
	static void ResetColliderHit(OctTree* root);
};


#endif // !QUADTREE_HPP
