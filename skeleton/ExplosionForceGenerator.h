#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class ExplosionForceGenerator : public ForceGenerator {
public:
	ExplosionForceGenerator(const Vector3& pos, float rad) : pos_(pos), rd(rad) {
		expArea = new Particle(pos, { 0,0,0 }, 0, { 0,0,0 }, { 0,0,0,0.2 },rd, 0);
	}
	~ExplosionForceGenerator() { delete expArea; }
	virtual void updateForce(Particle* particle, double t) {
		if (fabs(particle->inv_mass) < 1e-10) return;

		float x = (particle->posit.p.x - expArea->posit.p.x) * (particle->posit.p.x - expArea->posit.p.x);
		float y = (particle->posit.p.y - expArea->posit.p.y) * (particle->posit.p.y - expArea->posit.p.y);
		float z = (particle->posit.p.z - expArea->posit.p.z) * (particle->posit.p.z - expArea->posit.p.z);

		if (sqrt(x + y + z) < rd) {
			Vector3 force = (particle->posit.p - expArea->posit.p)/10;
			particle->addForce(force * force.normalize());
		}

		
	}


protected:

	Particle* expArea;

	Vector3 pos_;
	float rd;
};
