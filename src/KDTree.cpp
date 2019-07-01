/**
	Purpose: An unused KDTree implementation that was replaced by an octree during the various improvements I made to the project. I left it in because it could have been useful.

	@author Tim Akermann
*/


#include "KDTree.h"
#include "glm.hpp"

KDNode* KDNode::newNode(const float arr[], KDNode* parent)
{
	KDNode* temp = new KDNode;

	for (size_t i = 0; i < K; i++)
	{
		temp->point[i] = arr[i];
	}

	temp->right = temp->left = nullptr;
	return temp;
}

KDNode* KDNode::insert(KDNode* root, float point[], unsigned int depth) const
{
	if (root == nullptr)return newNode(point, root);

	//If added collider can not possibly fit into root, return null
	//If collider can not fit into left or right add to this node
	//If this node is full, 
	const unsigned int  cd = depth % K;

	if (point[cd] < root->point[cd]) //if box can be entirely enclosed by left
	{
		root->left = insert(root->left, point, depth + 1);
	}
	else //if box can be entirely enclosed right
	{
		root->right = insert(root->right, point, depth + 1);
	}
	//else add thes box to the current node.
	
	return root;
}

KDNode* KDNode::insert(KDNode* root, float point[]) const
{
	return insert(root, point, 0);
}

bool KDNode::comparePoints(float point1[], float point2[]) const
{
	for (size_t i = 0; i < K; i++)
	{
		if (glm::abs(point1[i] - point2[i]) > EPSILON)return false;
	}
	return true;
}

bool KDNode::search(KDNode* root, float point[], const unsigned int depth) const
{
	if (root == nullptr)return false;
	if (comparePoints(root->point, point))return true;

	const unsigned int cd = depth % K;

	if (point[cd] < root->point[cd])
	{
		return search(root->left, point, depth + 1);
	}
	return search(root->right, point, depth + 1);
}

bool KDNode::search(KDNode* root, float point[]) const
{
	return search(root, point, 0);
}

KDNode* KDNode::minNode(KDNode* x, KDNode* y, KDNode*z, const int d)
{
	KDNode* res = x;
	if (y != nullptr && y->point[d] < res->point[d])res = y;
	if (z != nullptr && z->point[d] < res->point[d])res = z;

	return res;
}

KDNode* KDNode::findMin(KDNode* root, const int d, const unsigned int depth) const
{
	if (root == nullptr)return nullptr;

	const unsigned int cd = depth % K;

	if (cd == d)
	{
		if (root->left == nullptr)
			return root;
		return findMin(root, d, depth + 1);
	}

	return minNode(root,
		findMin(root->left, d, depth + 1),
		findMin(root->right, d, depth + 1), d);
}

KDNode* KDNode::findMin(KDNode* root, const int d) const
{
	return findMin(root, d, 0);
}

void KDNode::copyPoint(float point1[], const float point2[])
{
	for (size_t i = 0; i < K; i++)
	{
		point1[i] = point2[i];
	}
}

KDNode* KDNode::deleteNode(KDNode* root, float point[], const unsigned int depth) const
{
	if (root == nullptr) return nullptr;


	const unsigned int cd = depth / K;
	if (comparePoints(root->point, point))
	{
		if (root->right != nullptr)
		{
			KDNode* min = findMin(root->right, cd);
			copyPoint(root->point, min->point);
			root->right = deleteNode(root->right, min->point, depth + 1);
		}
		else if (root->left != nullptr)
		{
			KDNode* min = findMin(root->left, cd);
			copyPoint(root->point, min->point);
			root->left = deleteNode(root->left, min->point, depth + 1);
		}
		else {
			delete root;

			return nullptr;
		}

		if (point[cd] < root->point[cd])
			root->left = deleteNode(root->left, point, depth + 1);
		else
			root->right = deleteNode(root->left, point, depth + 1);
		return root;
	}

	return nullptr;
}

KDNode* KDNode::deleteNode(KDNode* root, float point[]) const
{
	return deleteNode(root, point, 0);
}


bool KDNode::isEnclosing(KDNode* root, const float point[], const float extends[], unsigned int cd)
{

	if (root->point[cd] + root->extends[cd] < point[cd] + extends[cd])return false;
	if (root->point[cd] - root->extends[cd] > point[cd] - extends[cd])return false;
	return true;
}