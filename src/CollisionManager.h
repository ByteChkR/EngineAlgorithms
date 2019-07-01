#ifndef COLLISIONMANAGER_HPP

#define COLLISIONMANAGER_HPP

#include "mge/core/GameObject.hpp"
#include "OBBCollider.h"
#include "glm.hpp"
#include <vector>
#include "OctTree.h"


class CollisionManager
{
public:
	static CollisionManager* instance;
	CollisionManager();
	~CollisionManager();
	int CheckCollisions() const;
	static std::vector<Collider*> _activeCollider;
	static std::vector<Collider*> _passiveCollider;
	static std::vector<OctTree*> _leafNodes;
	static OctTree* _staticColliderTree;
	static int actualChecks;
};

#endif // !COLLISIONMANAGER_HPP
