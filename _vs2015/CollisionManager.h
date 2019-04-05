#ifndef COLLISIONMANAGER_HPP

#define COLLISIONMANAGER_HPP

#include "mge/core/GameObject.hpp"
#include "StaticOBBCollider.h"
#include "glm.hpp"
#include <vector>


class CollisionManager
{
public:
	static CollisionManager* instance;
	CollisionManager();
	~CollisionManager();
	int CheckCollisions();
	static std::vector<Collider*> _activeCollider;
};

#endif // !COLLISIONMANAGER_HPP
