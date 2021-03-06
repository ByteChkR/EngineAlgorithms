#ifndef OCTTREE_HPP


#define OCTTREE_HPP

#include "glm.hpp"
#include <vector>
#include "OBBCollider.h"

enum Octants
{
	LEFTBACKTOP, LEFTFRONTTOP, LEFTBACKBOT, LEFTFRONTBOT,
	RIGHTBACKTOP, RIGHTFRONTTOP, RIGHTBACKBOT, RIGHTFRONTBOT
};

struct OctTree
{
public:
	~OctTree();
	static unsigned int MAX_LEVEL;
	static const int ROOT_EXTENDS = 512;
	static const float ROOT_RADIUS;
	static const int REMOVAL_DELAY = 5;
	OctTree *leftBackTop, *leftFrontTop,
		*rightBackTop, *rightFrontTop,
		*leftBackBot, *leftFrontBot,
		*rightBackBot, *rightFrontBot,
		*root;

	float extend, radius;
	int removeFrame;
	Octants octant;
	glm::vec3 point;
	std::vector<Collider*> dynamicCollider;
	std::vector<Collider*> staticCollider;
	static OctTree* createTree();
	static OctTree* createNode(OctTree* root, Octants octant, unsigned int depth);
	static bool isEnclosing(glm::vec3 rootpoint, float rootextend, Collider* object);
	static void insert(OctTree* root, Collider* object);
	void add(Collider* collider);
	bool ShouldRemove();
	static void ResetColliderHit(OctTree* root);

private:
	inline static void insert(OctTree* root, Collider* object, unsigned int depth);
	inline static glm::vec3 getChildPosition(OctTree* root, Octants octant, float extend);
	inline static bool isIntersecting(OctTree* root, Collider* object);
	inline static bool isIntersectingChild(OctTree* root, Octants octant, Collider* object);
	inline static bool isIntersecting(glm::vec3 rootPosition, float rootExtend, Collider* collider);
};


#endif // !QUADTREE_HPP
