#ifndef KDTREE_HPP

#define KDTREE_HPP
#include <vector>
#include "StaticOBBCollider.h"

const int K = 3;
const float EPSILON = 0.001f;

struct KDNode
{

	float point[3];
	std::vector<Collider*> collider;
	KDNode *left, *right, *parent;
	KDNode* newNode(float arr[], KDNode* parent);
	KDNode* insert(KDNode* root, float point[]);
	KDNode* insert(KDNode* root, float point[], unsigned int depth);
	bool comparePoints(float point1[], float point2[]);
	bool search(KDNode* root, float point[], unsigned int depth);
	bool search(KDNode* root, float point[]);
	KDNode* findMin(KDNode* root, int d, unsigned int depth);
	KDNode* findMin(KDNode* root, int d);
	KDNode* deleteNode(KDNode* root, float point[], unsigned int depth);
	KDNode* deleteNode(KDNode* rootm, float point[]);
	void copyPoint(float point1[], float point2[]);
	KDNode* minNode(KDNode* x, KDNode* y, KDNode* z, int d);

};

#endif // !KDTREE_HPP
