#pragma once

#include <list>
#include <random>
#include "core.hpp"
#include "Particle.h"


class ForceGenerator {
public:


	ForceGenerator() {}
	~ForceGenerator(){}

	virtual void updateForce(Particle* paticle, double duration) = 0;
	virtual void updateObjectForce(physx::PxRigidDynamic* obj, double duration) = 0;
	std::string nombre;
	double t = -1e10;


};