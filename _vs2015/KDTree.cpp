#include "KDTree.h"
#include "glm.hpp"

KDNode* KDNode::newNode(float arr[], KDNode* parent)
{
	KDNode* temp = new KDNode;

	for (size_t i = 0; i < K; i++)
	{
		temp->point[i] = arr[i];
	}

	temp->right = temp->left = nullptr;
	return temp;
}

KDNode* KDNode::insert(KDNode* root, float point[], unsigned int depth)
{
	if (root == nullptr)return newNode(point, root);

	//If added collider can not possibly fit into root, return null
	//If collider can not fit into left or right add to this node
	//If this node is full, 
	unsigned int  cd = depth % K;

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

KDNode* KDNode::insert(KDNode* root, float point[])
{
	return insert(root, point, 0);
}

bool KDNode::comparePoints(float point1[], float point2[])
{
	for (size_t i = 0; i < K; i++)
	{
		if (glm::abs(point1[i] - point2[i]) > EPSILON)return false;
	}
	return true;
}

bool KDNode::search(KDNode* root, float point[], unsigned int depth)
{
	if (root == nullptr)return false;
	if (comparePoints(root->point, point))return true;

	unsigned int cd = depth % K;

	if (point[cd] < root->point[cd])
	{
		return search(root->left, point, depth + 1);
	}
	return search(root->right, point, depth + 1);
}

bool KDNode::search(KDNode* root, float point[])
{
	return search(root, point, 0);
}

KDNode* KDNode::minNode(KDNode* x, KDNode* y, KDNode*z, int d)
{
	KDNode* res = x;
	if (y != nullptr && y->point[d] < res->point[d])res = y;
	if (z != nullptr && z->point[d] < res->point[d])res = z;

	return res;
}

KDNode* KDNode::findMin(KDNode* root, int d, unsigned int depth)
{
	if (root == nullptr)return nullptr;

	unsigned int cd = depth % K;

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

KDNode* KDNode::findMin(KDNode* root, int d)
{
	return findMin(root, d, 0);
}

void KDNode::copyPoint(float point1[], float point2[])
{
	for (size_t i = 0; i < K; i++)
	{
		point1[i] = point2[i];
	}
}

KDNode* KDNode::deleteNode(KDNode* root, float point[], unsigned int depth)
{
	if (root == nullptr) return nullptr;


	unsigned int cd = depth / K;
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
}

KDNode* KDNode::deleteNode(KDNode* root, float point[])
{
	return deleteNode(root, point, 0);
}


bool KDNode::isEnclosing(KDNode* root, float point1[], float extends1[], unsigned int cd)
{

	if (root->point[cd] + root->extends[cd] < point1[cd] + extends1[cd])return false;
	if (root->point[cd] - root->extends[cd] > point1[cd] - extends1[cd])return false;
	return true;
}