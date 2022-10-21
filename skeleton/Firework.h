#pragma once


#include "core.hpp"
#include "RenderUtils.hpp"
#include "Particle.h"
#include <list>


class Firework:public Particle {
	Firework(Vector3 pos, Vector3 vel, float damping, Vector3 accelerate, Vector4 color, int tam);
	~Firework();

	void update(double t);
	std::list<Particle*> explode();
};


