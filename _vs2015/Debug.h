#ifndef DEBUG_HPP
#include <string>

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

private:
	Debug();
};



#endif // 
