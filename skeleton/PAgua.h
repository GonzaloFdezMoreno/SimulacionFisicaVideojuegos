#pragma once

#include "core.hpp"
#include "RenderUtils.hpp"
#include "Particle.h"
//#include "GaussianParticleGenerator.h"
//#include "UniformParticleGenerator.h"

#include <list>
#include <random>


class PAgua:public Particle {
public:
	PAgua(Vector3 pos, Vector3 vel, float damping, Vector3 accelerate, Vector4 color, float tam,float mass);
	~PAgua();


	void update(double t) override;
	std::list<Particle*>  explode() override;
	
	bool explodes = false;

	bool ended = false;

protected:
	std::mt19937 rnd;
};


