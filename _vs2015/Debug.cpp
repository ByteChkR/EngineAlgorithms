#include "Debug.h"
#include <iostream>
#include <string>
#include "mge/config.hpp"

Debug::Debug()
{

}

void Debug::Log(std::string message, DebugLevel DebugLevel)
{
		std::cout << message << std::endl;
}

void Debug::LogError(std::string errorMessage)
{
	std::cerr << errorMessage << std::endl;
}