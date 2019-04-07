#ifndef KEYSBEHAVIOUR_HPP
#define KEYSBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "glm.hpp"

/**
 * KeysBehaviour allows you to move an object using the keyboard in its own local space.
 * Left right turns, forward back moves.
 */
class KeysBehaviour : public AbstractBehaviour
{
	public:
	    //move speed is in units per second, turnspeed in degrees per second
		KeysBehaviour(glm::vec3 pMoveSpeed = glm::vec3(5));
		virtual ~KeysBehaviour();
		virtual void update( float pStep );

    private:
        glm::vec3 _moveSpeed;

};

#endif // KEYSBEHAVIOUR_HPP
