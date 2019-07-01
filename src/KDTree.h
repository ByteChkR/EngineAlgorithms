#ifndef KDTREE_HPP

#define KDTREE_HPP
#include <vector>
#include "OBBCollider.h"

const int K = 3;
const float EPSILON = 0.001f;

struct KDNode
{
	float extends[K];
	float point[K];
	bool isEnclosing(KDNode* root, const float point[], const float extends[], unsigned int cd);
	std::vector<Collider*> collider;
	KDNode *left, *right, *parent;
	static KDNode* newNode(const float arr[], KDNode* parent);
	KDNode* insert(KDNode* root, float point[]) const;
	KDNode* insert(KDNode* root, float point[], unsigned int depth) const;
	bool comparePoints(float point1[], float point2[]) const;
	bool search(KDNode* root, float point[], unsigned int depth) const;
	bool search(KDNode* root, float point[]) const;
	KDNode* findMin(KDNode* root, int d, unsigned int depth) const;
	KDNode* findMin(KDNode* root, int d) const;
	KDNode* deleteNode(KDNode* root, float point[], unsigned int depth) const;
	KDNode* deleteNode(KDNode* root, float point[]) const;
	static void copyPoint(float point1[], const float point2[]);
	static KDNode* minNode(KDNode* x, KDNode* y, KDNode* z, int d);

};

#endif // !KDTREE_HPP
