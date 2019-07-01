#include <iostream>

#include "AbstractGame.hpp"
#include "mge/core/Renderer.hpp"
#include "mge/core/World.hpp"
#include "../_vs2015/Debug.h"

BenchmarkPreset* AbstractGame::currentPreset = nullptr;

AbstractGame::AbstractGame() :_window(NULL), _renderer(NULL), _world(NULL), _fps(0)
{
	//ctor
}

AbstractGame::~AbstractGame()
{
	//dtor
	delete manager;
	delete _window;
	delete _renderer;
	delete _world;
}

void AbstractGame::initialize() {
	_initializeWindow();
	_printVersionInfo();
	_initializeGlew();
	_initializeRenderer();
	_initializeWorld();
	_initializeScene();
	std::cout << "Engine initialized." << std::endl;
}

///SETUP

void AbstractGame::_initializeWindow() {
	//std::cout << "Initializing window..." << std::endl;
	_window = new sf::RenderWindow(sf::VideoMode(800, 600), "My Game!", sf::Style::Default, sf::ContextSettings(24, 8, 0, 3, 3));
	//_window->setVerticalSyncEnabled(true);
	std::cout << "Window initialized." << std::endl;
}

void AbstractGame::_printVersionInfo() {
	//std::cout << "Context info:" << std::endl;
	//std::cout << "----------------------------------" << std::endl;
	////print some debug stats for whoever cares
	//const GLubyte *vendor = glGetString(GL_VENDOR);
	//const GLubyte *renderer = glGetString(GL_RENDERER);
	//const GLubyte *version = glGetString(GL_VERSION);
	//const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	////nice consistency here in the way OpenGl retrieves values
	//GLint major, minor;
	//glGetIntegerv(GL_MAJOR_VERSION, &major);
	//glGetIntegerv(GL_MINOR_VERSION, &minor);

	//printf("GL Vendor : %s\n", vendor);
	//printf("GL Renderer : %s\n", renderer);
	//printf("GL Version (string) : %s\n", version);
	//printf("GL Version (integer) : %d.%d\n", major, minor);
	//printf("GLSL Version : %s\n", glslVersion);

	//std::cout << "----------------------------------" << std::endl << std::endl;
}

void AbstractGame::_initializeGlew() {
	//std::cout << "Initializing GLEW..." << std::endl;
	//initialize the opengl extension wrangler
	GLint glewStatus = glewInit();
	std::cout << "Initialized GLEW, status (1 == OK, 0 == FAILED):" << (glewStatus == GLEW_OK) << std::endl;
}

void AbstractGame::_initializeRenderer() {
	//setup our own renderer
	//std::cout << "Initializing renderer..." << std::endl;
	_renderer = new Renderer();
	_renderer->setClearColor(0, 0, 0);
	std::cout << "Renderer Initializing done." << std::endl;
}

void AbstractGame::_initializeWorld() {
	//setup the world
	_world = new World();
	std::cout << "World initialized." << std::endl;

	manager = new CollisionManager();
	std::cout << "Collision Manager initialized." << std::endl;
}

///MAIN GAME LOOP

void AbstractGame::run()
{
	new Debug(); //Setting up Debug
	//setting to calculate fps
	sf::Clock renderClock;
	sf::Clock physicsTimer;
	int frameCount = 0;
	sf::Time lag = sf::Time::Zero;
	sf::Clock lagClock;
	float timeSinceLastFPSCalculation = 0;

	sf::Time benchmarkTime = sf::seconds(currentPreset->_benchmarkTime);
	sf::Time currentTime = sf::Time::Zero;

	sf::Time delta;

	//settings to make sure the update loop runs at 60 fps
	sf::Time timePerFrame = sf::seconds(1.0f / 480.0f);
	sf::Clock updateClock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time realDeltaTime = sf::Time::Zero;

	int collisionChecksperFrame = 0;


	while (_window->isOpen() && benchmarkTime > currentTime) {
		delta = updateClock.restart();
		timeSinceLastUpdate += delta;
		currentTime += delta;




		collisionChecksperFrame = 0;

		if (timeSinceLastUpdate > timePerFrame)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			lagClock.restart(); //Reset the clock because it should only measure the lag within the while loop and not the whole rendering

			while (timeSinceLastUpdate > timePerFrame) {
				realDeltaTime = timePerFrame+lag;
				timeSinceLastUpdate -= realDeltaTime; //The Lag is added to the timeperframe
				_update(realDeltaTime.asSeconds());

				physicsTimer.restart();

				collisionChecksperFrame = CollisionManager::instance->CheckCollisions();
				Debug::LogCSV(realDeltaTime.asSeconds(), collisionChecksperFrame);

				lag = lagClock.restart();
				//Collision Detection
			}

			_render();
			_window->display();

			//fps count is updated once every 1 second
			frameCount++;
			timeSinceLastFPSCalculation += renderClock.restart().asSeconds();
			if (timeSinceLastFPSCalculation > 1) {
				_fps = frameCount / timeSinceLastFPSCalculation;
				timeSinceLastFPSCalculation -= 1;
				frameCount = 0;
			}

		}

		//empty the event queue
		_processEvents();
	}

	Debug::FlushCSV();
	//After that the game should close and save the logs to a folder with the current timestamp.(No Timestamps pure csv)
}

void AbstractGame::_update(float pStep) {
	_world->update(pStep);
}

void AbstractGame::_render() {
	_renderer->render(_world);
}

void AbstractGame::_processEvents()
{
	sf::Event event;
	bool exit = false;

	//we must empty the event queue
	while (_window->pollEvent(event)) {
		//give all system event listeners a chance to handle events
		//optionally to be implemented by you for example you could implement a
		//SystemEventDispatcher / SystemEventListener pair which allows Listeners to
		//register with the dispatcher and then do something like:
		//SystemEventDispatcher::dispatchEvent(event);

		switch (event.type) {
		case sf::Event::Closed:
			exit = true;
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape) {
				exit = true;
			}
			break;
		case sf::Event::Resized:
			//would be better to move this to the renderer
			//this version implements nonconstrained match viewport scaling
			glViewport(0, 0, event.size.width, event.size.height);
			break;

		default:
			break;
		}
	}

	if (exit) {
		_window->close();
	}
}



