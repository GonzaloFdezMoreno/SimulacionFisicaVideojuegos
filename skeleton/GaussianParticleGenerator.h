#pragma once
#include "ParticleGenerator.h"
#include <list>
#include <random>

class GaussianParticleGenerator:public ParticleGenerator {
protected:
	Vector3 std_dev_pos;
	Vector3 std_dev_vel;
	double std_dev_t;

	std::normal_distribution<double> dis{ 0,1 };
	
public:
	GaussianParticleGenerator(Vector3 std_dev_pos,Vector3 std_dev_vel);
	~GaussianParticleGenerator();
	std::list<Particle*> generateParticle();
};