#include <iostream>
#include <string>

#include "glm.hpp"

//#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
//#include "mge/core/Texture.hpp"
//#include "mge/core/Light.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/GameObject.hpp"

//#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
//#include "mge/materials/TextureMaterial.hpp"

//#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"
#include "mge/MGEDemo.hpp"

//construct the game class into _window, _renderer and hud (other parts are initialized by build)
MGEDemo::MGEDemo() :AbstractGame(), _hud(0)
{
}

void MGEDemo::initialize() {
	//setup the core part
	AbstractGame::initialize();

	//setup the custom part so we can display some text
	//std::cout << "Initializing HUD" << std::endl;
	_hud = new DebugHud(_window);
	std::cout << "HUD initialized." << std::endl;
}

//build the game _world
void MGEDemo::_initializeScene()
{
	Mesh* cubeMeshF = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");

	Camera* camera = new Camera("camera", glm::vec3(255, 512, 255));
	camera->rotate(glm::radians(-90.0f), glm::vec3(1, 0, 0));
	_world->add(camera);
	_world->setMainCamera(camera);


	for (int i = 0; i < currentPreset->_activeCount; i++)
	{
		float r1, r2, r3, r4, r5;
		r1 = (std::rand() / (float)RAND_MAX);
		r2 = (std::rand() / (float)RAND_MAX);
		r5 = (std::rand() / (float)RAND_MAX);
		r3 = 15 + (std::rand() / (float)RAND_MAX / 10);
		r4 = 50 + (std::rand() / (float)RAND_MAX / 45);
		GameObject* box1 = new GameObject("box1", glm::vec3(r1, r5, r2) * 512);
		box1->setMesh(cubeMeshF);
		box1->setMaterial(new ColorMaterial(glm::vec3(0, 1, 0)));

		box1->setBehaviour(new KeysBehaviour(
			glm::vec3(r1 - 0.5, r2 - 0.5, r2 - 0.5)));
		_world->add(box1);

		box1->setCollider(new Collider(box1, false, true, glm::vec3(1)));
	}
	for (int i = 0; i < currentPreset->_staticCount; i++)
	{
		float r1, r2, r3, r4, r5;
		r1 = (std::rand() / (float)RAND_MAX);
		r2 = (std::rand() / (float)RAND_MAX);
		r5 = (std::rand() / (float)RAND_MAX);
		r3 = 15 + (std::rand() / (float)RAND_MAX / 10);
		r4 = 50 + (std::rand() / (float)RAND_MAX / 45);
		GameObject* box1 = new GameObject("box1", glm::vec3(r1, r5, r2) * 512);
		box1->setMesh(cubeMeshF);
		box1->setMaterial(new ColorMaterial(glm::vec3(0, 1, 0)));
		_world->add(box1);
		box1->setCollider(new Collider(box1, true, false, glm::vec3(1)));
	}

}

void MGEDemo::_render() {
	AbstractGame::_render();
	_updateHud();
}

void MGEDemo::_updateHud() {
	std::string debugInfo = "";
	debugInfo += std::string("FPS:") + std::to_string((int)_fps) + "\n";

	_hud->setDebugInfo(debugInfo);
	_hud->draw();
}

MGEDemo::~MGEDemo()
{
	//dtor
}
