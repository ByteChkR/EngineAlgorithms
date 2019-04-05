#include "Debug.h"

std::vector<std::pair<int, int>> Debug::logs = std::vector<std::pair<int, int>>(14400);
std::ofstream Debug::csv;
int Debug::current = 0;

Debug::Debug()
{
	csv.open(".\\csv\\log"+std::to_string(std::time(nullptr))+".csv");

}

void Debug::LogCSV(int frameTime, int collisionChecks)
{
	
	logs[current] = std::pair<int, int>(frameTime, collisionChecks);
	current++;
}

void Debug::FlushCSV()
{
	for each (std::pair<int, int> pair in logs)
	{
		csv << std::to_string(pair.first) << ", " << std::to_string(pair.second)  << std::endl;
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