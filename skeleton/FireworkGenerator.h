#pragma once

#include "ParticleGenerator.h"
#include "Firework.h"
#include <list>
#include <random>

class FireworkGenerator {
protected:
	Vector3 std_dev_pos;
	Vector3 std_dev_vel;
	double std_dev_t;

	std::normal_distribution<double> dis{ 0,1 };
	std::normal_distribution<double> vel{ 15, 2 };

public:
	FireworkGenerator(Vector3 std_dev_pos, Vector3 std_dev_vel);
	~FireworkGenerator();
	std::list<Firework*> generateParticles(); 

	


};