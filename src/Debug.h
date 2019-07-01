#ifndef DEBUG_HPP
#define DEBUG_HPP
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>



enum DebugLevel
{
	CollisionsPerFrame,
	ActualCollisionChecks,
	FrameTime,
};


class Debug
{
public:
	static void Log(std::string message, DebugLevel DebugLevel);
	static void LogError(std::string message);
	static void LogCSV(float frameTime, int collisionChecks);
	static void FlushCSV();
	Debug();
	~Debug();
private:
	static int current;
	static std::ofstream csv;
	static std::vector<std::pair<float, int>> logs;
};



#endif // 
