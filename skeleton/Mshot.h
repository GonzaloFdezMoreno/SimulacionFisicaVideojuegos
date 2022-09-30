#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "Particle.h"


class Mshot:public Particle {

public:
	Mshot(double mass,Vector3 vel, Vector3 pos, float damping, Vector3 accelerate);
	~Mshot();

	
	void integrate(double t);

private:
	
	double mass;
	
};