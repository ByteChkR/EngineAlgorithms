#include <iostream>
#include <string>

#include "glm.hpp"

#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/GameObject.hpp"

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"

#include "mge/behaviours/RotatingBehaviour.hpp"
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
	std::cout << "Initializing HUD" << std::endl;
	_hud = new DebugHud(_window);
	std::cout << "HUD initialized." << std::endl << std::endl;
}

//build the game _world
void MGEDemo::_initializeScene()
{
	//MESHES

	//load a bunch of meshes we will be using throughout this demo
	//each mesh only has to be loaded once, but can be used multiple times:
	//F is flat shaded, S is smooth shaded (normals aligned or not), check the models folder!
	Mesh* planeMeshDefault = Mesh::load(config::MGE_MODEL_PATH + "plane.obj");
	Mesh* cubeMeshF = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");
	Mesh* sphereMeshS = Mesh::load(config::MGE_MODEL_PATH + "sphere_smooth.obj");

	//MATERIALS

	//create some materials to display the cube, the plane and the light
	AbstractMaterial* lightMaterial = new ColorMaterial(glm::vec3(1, 1, 0));
	AbstractMaterial* runicStoneMaterial = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png"));

	//SCENE SETUP

   //add camera first (it will be updated last)
	Camera* camera = new Camera("camera", glm::vec3(50, 100, 50));
	camera->rotate(glm::radians(-90.0f), glm::vec3(1, 0, 0));
	_world->add(camera);
	_world->setMainCamera(camera);

	////add the floor
	//GameObject* plane = new GameObject ("plane", glm::vec3(0,0,0));
	//plane->scale(glm::vec3(5,5,5));
	//plane->setMesh(planeMeshDefault);
	//plane->setMaterial(runicStoneMaterial);
	//_world->add(plane);

	////add a spinning sphere
	//GameObject* sphere = new GameObject ("sphere", glm::vec3(0,0,0));
	//sphere->scale(glm::vec3(2.5,2.5,2.5));
	//sphere->setMesh (sphereMeshS);
	//sphere->setMaterial(runicStoneMaterial);
	//sphere->setBehaviour (new RotatingBehaviour());
	//_world->add(sphere);

	////add a light. Note that the light does ABSOLUTELY ZIP! NADA ! NOTHING !
	////It's here as a place holder to get you started.
	////Note how the texture material is able to detect the number of lights in the scene
	////even though it doesn't implement any lighting yet!

	//Light* light = new Light("light", glm::vec3(0,4,0));
	//light->scale(glm::vec3(0.1f, 0.1f, 0.1f));
	//light->setMesh(cubeMeshF);
	//light->setMaterial(lightMaterial);
	//light->setBehaviour(new KeysBehaviour(25));
	//_world->add(light);



	for (size_t i = 0; i < 100; i++)
	{
		float r1, r2, r3, r4;
		r1 = (std::rand() / (float)RAND_MAX);
		r2 = (std::rand() / (float)RAND_MAX);
		r3 = 15 + (std::rand() / (float)RAND_MAX / 10);
		r4 = 50 + (std::rand() / (float)RAND_MAX / 45);
		GameObject* box1 = new GameObject("box1", glm::vec3(r1, 0, r2) * 100);
		box1->setMesh(cubeMeshF);
		box1->setMaterial(new ColorMaterial(glm::vec3(0, 1, 0)));

		box1->setBehaviour(new KeysBehaviour(
			(std::rand() % 2 == 0) ? r3 : -r3, 
			(std::rand() % 2 == 0) ? r4 : -r4));
		box1->setCollider(new Collider(box1, true, true, glm::vec3(1)));
		_world->add(box1);
	}


	GameObject* box2 = new GameObject("box2", glm::vec3(2, 0, 2));
	box2->setMesh(cubeMeshF);
	box2->setMaterial(new ColorMaterial(glm::vec3(0, 1, 0)));
	box2->setCollider(new Collider(box2, true, true, glm::vec3(1)));
	box2->setBehaviour(new KeysBehaviour(25, 75));
	_world->add(box2);

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