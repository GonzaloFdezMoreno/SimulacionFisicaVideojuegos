#pragma once

#include "core.hpp"
#include "RenderUtils.hpp"
#include "Particle.h"
//#include "GaussianParticleGenerator.h"
//#include "UniformParticleGenerator.h"
#include <list>
#include <random>


class Firework:public Particle {
public:
	Firework(Vector3 pos, Vector3 vel, float damping, Vector3 accelerate, Vector4 color, int tam);
	~Firework();


	void update(double t);
	std::list<Particle*>  explode();
	bool explodes = false;

	bool ended = false;

protected:
	std::mt19937 rnd;
};


