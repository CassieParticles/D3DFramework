#pragma once

#include <random>
#include <chrono>

class Random
{
public:
	static Random* Instance();
	//Random number from 0-1
	float genRand();
	//Randon float from a-b
	float genRand(float a, float b);
	//Random integer from a-b
	int genRand(int a, int b);

	void setSeed(unsigned int seed);
protected:
	static Random* instance;
	Random() = default;
	~Random() = default;


	std::mt19937 rand;
};