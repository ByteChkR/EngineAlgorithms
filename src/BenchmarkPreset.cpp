/**
	Purpose: Holds the parameters of a benchmark configuration

	@author Tim Akermann
*/

#include "BenchmarkPreset.h"

BenchmarkPreset::BenchmarkPreset(float benchMarkTime, int activeCount, int staticCount, int treeDepth, bool enableCircleTest, bool enableNodeRemoval, bool enableOldDynamicRemoval)
	:_benchmarkTime(benchMarkTime), _activeCount(activeCount), _staticCount(staticCount), _treeDepth(treeDepth), _enableCircleTest(enableCircleTest), _enableNodeRemoval(enableNodeRemoval), _enableOldDynamicRemoval(enableOldDynamicRemoval)
{

}



std::string BenchmarkPreset::getLogName() const
{
	std::string ret="";
	ret += std::to_string(_activeCount);
	ret += "Dx";
	ret += std::to_string(_staticCount);
	ret += "S_Tree";
	ret += std::to_string(_treeDepth);
	ret += "_C";
	ret += std::to_string(_enableCircleTest);
	ret += "_NR";
	ret += std::to_string(_enableNodeRemoval);
	ret += "_ODR";
	ret += std::to_string(_enableOldDynamicRemoval);
	ret += "_";
	return ret;

}
