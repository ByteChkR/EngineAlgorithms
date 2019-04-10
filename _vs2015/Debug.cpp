#include "Debug.h"
#include "mge/core/AbstractGame.hpp"

std::vector<std::pair<float, int>> Debug::logs = std::vector<std::pair<float, int>>(14400);
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

	logs[current] = std::pair<float, int>(frameTime, collisionChecks);
	current++;
}

void Debug::FlushCSV()
{
	std::string germanySucks = "";
	for each (std::pair<float, int> pair in logs)
	{
		germanySucks = std::to_string(pair.first);
		csv << germanySucks << ", " << std::to_string(pair.second) << std::endl;
	}
}

void Debug::Log(std::string message, DebugLevel DebugLevel)
{
	std::cout << message << std::endl;
}

void Debug::LogError(std::string errorMessage)
{
	std::cerr << errorMessage << std::endl;
}