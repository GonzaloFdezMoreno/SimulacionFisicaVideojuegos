#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class WindForceGenerator : public ForceGenerator {
public:
	WindForceGenerator(const Vector3& w) {
		_windir = w;
	}
	~WindForceGenerator() {}
	virtual void updateForce(Particle* particle, double t) {
		particle->posit = physx::PxTransform(particle->posit.p.x + particle->veloc.x * t, particle->posit.p.y + particle->veloc.y * t, particle->posit.p.z + particle->veloc.z * t);
		//con damping
		particle->veloc += _windir * ;
		particle->veloc *= pow(particle->damp, t);

	}
	//inline void setGravity(Vector3 g) { _gravity = g; }

protected:
	Vector3 _windir;
};