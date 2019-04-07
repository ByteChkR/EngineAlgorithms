#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Window/Keyboard.hpp>

KeysBehaviour::KeysBehaviour(glm::vec3 pMoveSpeed) : AbstractBehaviour(), _moveSpeed(pMoveSpeed)
{

}

KeysBehaviour::~KeysBehaviour()
{
}

void KeysBehaviour::update(float pStep)
{

	if (_owner->getLocalPosition().x < 0 || _owner->getLocalPosition().x > 1024)
	{
		_moveSpeed.x = -_moveSpeed.x;
	}
	else if (_owner->getLocalPosition().y < 0 || _owner->getLocalPosition().y > 1024)
	{
		_moveSpeed.y = -_moveSpeed.y;
	}
	else if (_owner->getLocalPosition().z < 0 || _owner->getLocalPosition().z > 1024)
	{
		_moveSpeed.z = -_moveSpeed.z;
	}
	//translate the object in its own local space
	_owner->setLocalPosition(_owner->getLocalPosition() + _moveSpeed);



	//we can also translate directly, basically we take the z axis from the matrix
	//which is normalized and multiply it by moveSpeed*step, then we add it to the
	//translation component
	//glm::mat4 transform = _owner->getTransform();
	//transform[3] += transform[2] * moveSpeed*pStep;
	//_owner->setTransform(transform);

	//rotate the object in its own local space
	//_owner->rotate( glm::radians(turnSpeed*pStep), glm::vec3(1.0f, 1.0f, 0.0f ) );

	//NOTE:
	//The reason the above happens in the local space of the object and not in the world space
	//is that we use the _owner->translate / rotate shortcuts which in turn call glm::rotate / glm::translate
	//The methods multiply the current transform with the translation/rotation matrix from left to right
	//meaning everything happens in local space.
}
