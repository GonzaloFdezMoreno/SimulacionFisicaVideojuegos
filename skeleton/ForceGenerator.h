#pragma once

#include <list>
#include <random>
#include "Particle.h"


class ForceGenerator {
public:


	ForceGenerator() {}
	~ForceGenerator(){}

	virtual void updateForce(Particle* paticle, double duration) = 0;
	std::string nombre;
	double t = -1e10;


};