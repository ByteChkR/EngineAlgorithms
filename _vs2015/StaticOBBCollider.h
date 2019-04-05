#ifndef COLLIDER_HPP

#define COLLIDER_HPP
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "glm.hpp"
#include "mge/core/GameObject.hpp"
#include <vector>
#include "mge/materials/ColorMaterial.hpp"
class Collider
{
public:
	Collider(GameObject* owner, bool isStatic, bool hasRotation, glm::vec3 halfExtents);
	glm::vec3 halfExtents;
	bool Check(Collider* other);
	bool CheckCirlce(Collider* other);
	bool IsStatic();
	bool HasRotation();
	void SetHit(bool isHit);
	static float EPSILON;
	GameObject* GetOwner();
	float GetSqrRadius();
private :
	bool _isStatic;
	bool _hasRotation;
	float _sqrRadius;
	GameObject* _owner;
};

#endif // !STATICOBBCOLLIDER_HPP
