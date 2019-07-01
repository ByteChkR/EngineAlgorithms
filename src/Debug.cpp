/**

	Purpose: Wrapper for logging the benchmark to disk.
	@author Tim Akermann
*/
#include "Debug.h"
#include "mge/core/AbstractGame.hpp"



std::vector<std::pair<float, int>> Debug::logs = std::vector<std::pair<float, int>>();
std::ofstream Debug::csv;
int Debug::current = 0;

Debug::Debug()
{
	current = 0;
	logs.clear();
	csv = std::ofstream();
	csv.open(".\\csv\\" + AbstractGame::currentPreset->getLogName() + std::to_string(std::time(nullptr)) + ".txt");

}

Debug::~Debug()
{
	logs.clear();
	current = 0;
}

void Debug::LogCSV(float frameTime, int collisionChecks)
{

	logs.push_back(std::pair<float, int>(frameTime, collisionChecks));
	current++;
}

void Debug::FlushCSV()
{
	std::string germanySucks = ""; //Well..... For some reason some german guy decided that all decimals are written with a , as the divider.......... CSV is basically not useful in germany if you dont specifically change the string representation to have a . instead of a ,
	for each (std::pair<float, int> pair in logs)
	{
		germanySucks = std::to_string(pair.first);
		csv << germanySucks << ", " << std::to_string(pair.second) << std::endl; //Germany sucks. 
	}
}

void Debug::Log(const std::string message)
{
	std::cout << message << std::endl;
}

void Debug::LogError(const std::string errorMessage)
{
	std::cerr << errorMessage << std::endl;
}