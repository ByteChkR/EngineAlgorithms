/**
	Purpose: Defines the OBB Collider

	@author Tim Akermann
*/

#include "OBBCollider.h"
#include "mge/core/GameObject.hpp"
#include "glm.hpp"
#include "CollisionManager.h"
#include "mge/materials/ColorMaterial.hpp"

float Collider::EPSILON = 0.0001f;


Collider::Collider(GameObject* owner, const bool isStatic, bool hasRotation, glm::vec3 halfExtents)
{
	_hasRotation = hasRotation;
	_isStatic = isStatic;
	_owner = owner;
	this->halfExtents = halfExtents;
	_sqrRadius = halfExtents[0] * halfExtents[0] + halfExtents[1] * halfExtents[1] + halfExtents[2] * halfExtents[2];
	_radius = glm::sqrt(_sqrRadius);
	if (_isStatic)
	{
		OctTree::insert(CollisionManager::_staticColliderTree, this);
		CollisionManager::_passiveCollider.push_back(this);
	}
	else
		CollisionManager::_activeCollider.push_back(this);

}

float Collider::GetRadius() const
{
	return _radius;
}

void Collider::SkipNext()
{
	_skipTreeRemoval = true;
}

bool Collider::ShouldSkip()
{
	bool ret = _skipTreeRemoval;
	_skipTreeRemoval = false;
	return ret;

}

void Collider::SetHit(bool isHit) const
{
	if (GetOwner()->getMaterial() != nullptr)
		static_cast<ColorMaterial*>(GetOwner()->getMaterial())->setDiffuseColor(isHit ? glm::vec3(1, 0, 0) : glm::vec3(0, 1, 0));
}

bool Collider::HasRotation() const
{
	return _hasRotation;
}

GameObject* Collider::GetOwner() const
{
	return _owner;
}

bool Collider::Check(Collider* other)
{
	float rthis, rother;
	glm::mat4 thisTransform = _hasRotation ? GetOwner()->getTransform() : glm::mat4(1);
	glm::mat4 otherTransform = other->HasRotation() ? other->GetOwner()->getTransform() : glm::mat4(1);

	glm::mat3 R, ABSR;
	for (size_t i = 3; --i;)
	{
		for (size_t j = 3; --j;)
		{
			glm::vec3 thisAxis, otherAxis;
			thisAxis = glm::vec3(thisTransform[i]);
			otherAxis = glm::vec3(otherTransform[j]);
			R[i][j] = glm::dot(thisAxis, otherAxis);
		}
	}


	glm::vec3 a_to_b = other->GetOwner()->getLocalPosition() - GetOwner()->getLocalPosition();


	a_to_b = glm::vec3(
		glm::dot(a_to_b, glm::vec3(thisTransform[0])),
		glm::dot(a_to_b, glm::vec3(thisTransform[1])),
		glm::dot(a_to_b, glm::vec3(thisTransform[2])));

	for (size_t i = 3; --i;)
	{
		for (size_t j = 3; --j;)
		{
			ABSR[i][j] = glm::abs(R[i][j]) + EPSILON;
		}
	}

	for (size_t i = 3; --i;)
	{
		rthis = halfExtents[i];
		rother =
			other->halfExtents[0] * ABSR[i][0] +
			other->halfExtents[1] * ABSR[i][1] +
			other->halfExtents[2] * ABSR[i][2];
		if (glm::abs(a_to_b[i]) > rthis + rother)return false;
	}

	for (size_t i = 3; --i;)
	{
		rthis =
			halfExtents[0] * ABSR[0][i] +
			halfExtents[1] * ABSR[1][i] +
			halfExtents[2] * ABSR[2][i];
		rother = other->halfExtents[i];
		if (glm::abs(
			a_to_b[0] * R[0][i] +
			a_to_b[1] * R[1][i] +
			a_to_b[2] * R[2][i]) > rthis + rother)return false;
	}


	rthis = halfExtents[1] * ABSR[2][0] + halfExtents[2] * ABSR[1][0];
	rother = other->halfExtents[1] * ABSR[0][2] + other->halfExtents[2] * ABSR[0][1];
	if (glm::abs(a_to_b[2] * R[1][0] - a_to_b[1] * R[2][0]) > rthis + rother)return false;

	rthis = halfExtents[1] * ABSR[2][1] + halfExtents[2] * ABSR[1][1];
	rother = other->halfExtents[0] * ABSR[0][2] + other->halfExtents[2] * ABSR[0][0];
	if (glm::abs(a_to_b[2] * R[1][2] - a_to_b[1] * R[2][2]) > rthis + rother)return false;

	rthis = halfExtents[0] * ABSR[2][0] + halfExtents[2] * ABSR[0][0];
	rother = other->halfExtents[1] * ABSR[1][2] + other->halfExtents[2] * ABSR[1][1];
	if (glm::abs(a_to_b[0] * R[2][0] - a_to_b[2] * R[0][0]) > rthis + rother)return false;

	rthis = halfExtents[0] * ABSR[2][1] + halfExtents[2] * ABSR[0][1];
	rother = other->halfExtents[0] * ABSR[1][2] + other->halfExtents[2] * ABSR[1][0];
	if (glm::abs(a_to_b[0] * R[2][1] - a_to_b[2] * R[0][1]) > rthis + rother)return false;

	rthis = halfExtents[0] * ABSR[2][2] + halfExtents[2] * ABSR[0][2];
	rother = other->halfExtents[0] * ABSR[1][1] + other->halfExtents[1] * ABSR[1][0];
	if (glm::abs(a_to_b[0] * R[2][2] - a_to_b[2] * R[0][2]) > rthis + rother)return false;

	rthis = halfExtents[0] * ABSR[1][0] + halfExtents[1] * ABSR[0][0];
	rother = other->halfExtents[1] * ABSR[2][2] + other->halfExtents[2] * ABSR[2][1];
	if (glm::abs(a_to_b[1] * R[0][0] - a_to_b[0] * R[1][0]) > rthis + rother)return false;

	rthis = halfExtents[0] * ABSR[1][1] + halfExtents[1] * ABSR[0][1];
	rother = other->halfExtents[0] * ABSR[2][2] + other->halfExtents[2] * ABSR[2][0];
	if (glm::abs(a_to_b[1] * R[0][1] - a_to_b[0] * R[1][1]) > rthis + rother)return false;

	rthis = halfExtents[0] * ABSR[1][2] + halfExtents[1] * ABSR[0][2];
	rother = other->halfExtents[0] * ABSR[2][1] + other->halfExtents[1] * ABSR[2][0];
	if (glm::abs(a_to_b[1] * R[0][2] - a_to_b[0] * R[1][2]) > rthis + rother)return false;

	return true;
	//SAT GOES HERE
}

bool Collider::CheckCirlce(Collider* other) const
{
	const auto dist = glm::fastDistance(GetOwner()->getLocalPosition(), other->GetOwner()->getLocalPosition());
	return dist * dist < other->GetSqrRadius() + GetSqrRadius();
}

bool Collider::IsStatic() const
{
	return _isStatic;
}

float Collider::GetSqrRadius() const
{
	return _sqrRadius;
}
