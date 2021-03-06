/**
	Purpose: Holds the parameters of a benchmark configuration

	@author Tim Akermann
*/

#ifndef BENCHMARKPRESET_HPP

#define BENCHMARKPRESET_HPP

#include <string>

struct BenchmarkPreset
{
public:
	BenchmarkPreset(float benchMarkTime, int activeCount, int staticCount, int treeDepth, bool enableCircleTest, bool enableNodeRemoval, bool
	                enableOldDynamicRemoval);
	float _benchmarkTime;
	int _activeCount, _staticCount, _treeDepth;
	bool _enableCircleTest, _enableNodeRemoval, _enableOldDynamicRemoval;
	std::string getLogName() const;
};

#endif // !BENCHMARKPRESET_HPP
