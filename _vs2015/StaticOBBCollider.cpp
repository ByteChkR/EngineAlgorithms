#include "StaticOBBCollider.h"
#include "mge/core/GameObject.hpp"
#include "glm.hpp"
#include "CollisionManager.h"
#include "mge/materials/ColorMaterial.hpp"

float Collider::EPSILON = 0.0001;

Collider::Collider(GameObject* owner, bool isStatic, bool hasRotation, glm::vec3 halfExtents)
{
	_hasRotation = hasRotation;
	_isStatic = isStatic;
	_owner = owner;
	this->halfExtents = halfExtents;
	CollisionManager::_activeCollider.push_back(this);
	//REGISTER IN SOME ARRAY FOR THE COLLISION MANAGER
}

void Collider::SetHit(bool isHit)
{
	((ColorMaterial*)GetOwner()->getMaterial())->setDiffuseColor(isHit ? glm::vec3(1, 0, 0) : glm::vec3(0, 1, 0));
}

bool Collider::HasRotation()
{
	return _hasRotation;
}

GameObject* Collider::GetOwner()
{
	return _owner;
}

bool Collider::Check(Collider* other)
{
	float rthis, rother;
	glm::mat4 thisTransform, otherTransform;
	thisTransform = _hasRotation ? GetOwner()->getTransform() : glm::mat4(1);
	otherTransform = other->HasRotation() ? other->GetOwner()->getTransform() : glm::mat4(1);

	glm::mat3 R, ABSR;
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			glm::vec3 thisAxis, otherAxis;
			thisAxis = glm::vec3(thisTransform[i]);
			otherAxis = glm::vec3(otherTransform[j]);
			R[i][j] = glm::dot(thisAxis, otherAxis);
		}
	}

	glm::vec3 aToB = other->GetOwner()->getLocalPosition() - GetOwner()->getLocalPosition();

	aToB = glm::vec3(
		glm::dot(aToB, glm::vec3(thisTransform[0])),
		glm::dot(aToB, glm::vec3(thisTransform[1])),
		glm::dot(aToB, glm::vec3(thisTransform[2])));

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			ABSR[i][j] = glm::abs(R[i][j]) + EPSILON;
		}
	}

	for (size_t i = 0; i < 3; i++)
	{
		rthis = halfExtents[i];
		rother =
			other->halfExtents[0] * ABSR[i][0] +
			other->halfExtents[1] * ABSR[i][1] +
			other->halfExtents[2] * ABSR[i][2];
		if (glm::abs(aToB[i]) > rthis + rother)return false;
	}

	for (size_t i = 0; i < 3; i++)
	{
		rthis =
			halfExtents[0] * ABSR[0][i] +
			halfExtents[1] * ABSR[1][i] +
			halfExtents[2] * ABSR[2][i];
		rother = other->halfExtents[i];
		if (glm::abs(
			aToB[i] * R[0][i] + 
			aToB[1] * R[1][i] + 
			aToB[2] * R[2][i]) > rthis + rother)return false;
	}


	rthis = halfExtents[1] * ABSR[2][0] + halfExtents[2] * ABSR[1][0];
	rother = other->halfExtents[1] * ABSR[0][2] + other->halfExtents[2] * ABSR[0][1];
	if (glm::abs(aToB[2] * R[1][0] - aToB[1] * R[2][0]) > rthis + rother)return false;

	rthis = halfExtents[1] * ABSR[2][1] + halfExtents[2] * ABSR[1][1];
	rother = other->halfExtents[0] * ABSR[0][2] + other->halfExtents[2] * ABSR[0][0];
	if (glm::abs(aToB[2] * R[1][2] - aToB[1] * R[2][2]) > rthis + rother)return false;

	rthis = halfExtents[0] * ABSR[2][0] + halfExtents[2] * ABSR[0][0];
	rother = other->halfExtents[1] * ABSR[1][2] + other->halfExtents[2] * ABSR[1][1];
	if (glm::abs(aToB[0] * R[2][0] - aToB[2] * R[0][0]) > rthis + rother)return false;

	rthis = halfExtents[0] * ABSR[2][1] + halfExtents[2] * ABSR[0][1];
	rother = other->halfExtents[0] * ABSR[1][2] + other->halfExtents[2] * ABSR[1][0];
	if (glm::abs(aToB[0] * R[2][1] - aToB[2] * R[0][1]) > rthis + rother)return false;

	rthis = halfExtents[0] * ABSR[2][2] + halfExtents[2] * ABSR[0][2];
	rother = other->halfExtents[0] * ABSR[1][1] + other->halfExtents[1] * ABSR[1][0];
	if (glm::abs(aToB[0] * R[2][2] - aToB[2] * R[0][2]) > rthis + rother)return false;

	rthis = halfExtents[0] * ABSR[1][0] + halfExtents[1] * ABSR[0][0];
	rother = other->halfExtents[1] * ABSR[2][2] + other->halfExtents[2] * ABSR[2][1];
	if (glm::abs(aToB[1] * R[0][0] - aToB[0] * R[1][0]) > rthis + rother)return false;

	rthis = halfExtents[0] * ABSR[1][1] + halfExtents[1] * ABSR[0][1];
	rother = other->halfExtents[0] * ABSR[2][2] + other->halfExtents[2] * ABSR[2][0];
	if (glm::abs(aToB[1] * R[0][1] - aToB[0] * R[1][1]) > rthis + rother)return false;

	rthis = halfExtents[0] * ABSR[1][2] + halfExtents[1] * ABSR[0][2];
	rother = other->halfExtents[0] * ABSR[2][1] + other->halfExtents[1] * ABSR[2][0];
	if (glm::abs(aToB[1] * R[0][2] - aToB[0] * R[1][2]) > rthis + rother)return false;

	return true;
	//SAT GOES HERE
}

bool Collider::CheckCirlce(Collider* other)
{
	return false;
	//IMPROVEMENT 1: Adding circle test.
}

//IMPROVEMENT 4: If collision occurred on this object already(on this frame) skip further collision tests(we are only changing colors. Thats a practical optimization.
//				not really an optimization thats applicable for general collision detection but especially useful for this task.

bool Collider::IsStatic()
{
	//IMPROVEMENT 3: Only Checking Active Colliders against static colliders.
	return _isStatic;
}
