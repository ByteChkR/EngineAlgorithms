#include <iostream>

#include "mge/core/AbstractGame.hpp"
#include "mge/MGEDemo.hpp"
#include "../_vs2015/BenchmarkPreset.h"

/**
 * Main entry point for the Micro Engine.

 * Design goals:
 * - correct division of OpenGL into appropriate wrapper classes
 * - simple design
 * - each class should know as little as possible about other classes and non related parts of OpenGL
 * - the engine must allow different objects with different transforms, meshes, materials (shaders) etc
 * - consistent coding conventions
 * - reusable and extendable core set of classes which should require no modification
 *   (in other words it is possible to have a working "empty" example)
 *
 * All documentation is contained within the HEADER files, not the CPP files if possible.
 *
 */
int main()
{
	std::vector<BenchmarkPreset> presets = std::vector<BenchmarkPreset>();

	float benchmarkTime = 300;

	//presets.push_back(BenchmarkPreset(30, 100, 100, 4, true, false, false)); //Base Line
	//presets.push_back(BenchmarkPreset(30, 100, 1000, 4, true, false, false)); //Base Line
	//presets.push_back(BenchmarkPreset(30, 1000, 100, 4, true, false, false)); //Base Line
	//presets.push_back(BenchmarkPreset(30, 1000, 1000, 4, true, false, false)); //Base Line
	//presets.push_back(BenchmarkPreset(30, 250, 250, 4, true, false, false)); //Base Line
	//presets.push_back(BenchmarkPreset(30, 500, 500, 4, true, false, false)); //Base Line
	//presets.push_back(BenchmarkPreset(30, 750, 750, 4, true, false, false)); //Base Line
	presets.push_back(BenchmarkPreset(30, 3000, 7000, 4, true, false, false)); //Base Line

	//for (size_t statics = 1000; statics <= 3000; statics+=1000)
	//{
	//	for (size_t dynamics = 1000; dynamics <= 3000; dynamics+=1000)
	//	{
	//		for (size_t treeDepth = 0; treeDepth < 5; treeDepth++)
	//		{
	//			for (size_t circle = 0; circle < 2; circle++)
	//			{
	//				presets.push_back(BenchmarkPreset(benchmarkTime, dynamics, statics, treeDepth, circle, true, false));
	//				presets.push_back(BenchmarkPreset(benchmarkTime, dynamics, statics, treeDepth, circle, true, true));
	//				presets.push_back(BenchmarkPreset(benchmarkTime, dynamics, statics, treeDepth, circle, false, false));
	//			}
	//		}
	//	}
	//}

	for (size_t i = 0; i < presets.size(); i++)
	{
		std::srand(0);
		std::cout << "Starting Preset:" << std::to_string(i) << std::endl;
		AbstractGame::currentPreset = &presets[i];
		AbstractGame* game = new MGEDemo();
		game->initialize();
		game->run();

		delete game;
	}

    

    return 0;
}



