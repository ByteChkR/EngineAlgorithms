#ifndef COLLIDER_HPP

#define COLLIDER_HPP
#include "glm.hpp"
class GameObject;
class Collider
{
public:
	Collider(GameObject* owner, bool isStatic, bool hasRotation, glm::vec3 halfExtents);
	glm::vec3 halfExtents;
	bool Check(Collider* other);
	bool CheckCirlce(Collider* other) const;
	bool IsStatic() const;
	bool HasRotation() const;
	void SetHit(bool isHit) const;
	static float EPSILON;
	GameObject* GetOwner() const;
	float GetSqrRadius() const;
	float GetRadius() const;
	bool ShouldSkip();
	void SkipNext();
private :
	bool _isStatic;
	bool _skipTreeRemoval{};
	bool _hasRotation;
	float _sqrRadius;
	float _radius;
	GameObject* _owner;
};

#endif // !OBBCollider_HPP
