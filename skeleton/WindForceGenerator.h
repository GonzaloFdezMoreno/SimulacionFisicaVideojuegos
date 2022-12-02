#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class WindForceGenerator : public ForceGenerator {
public:
	WindForceGenerator(const Vector3& w,float ka,float kb):_windir(w),k1(ka),k2(kb) {
		area = new Particle({20,100,20}, {0,0,0}, 0, {0,0,0}, {0,0,0,0.0}, 20, 0,false);
	}
	~WindForceGenerator() { delete area; }
	virtual void updateForce(Particle* particle, double t) {
		if (fabs(particle->inv_mass) < 1e-10) return;


		float x = (particle->posit.p.x - area->posit.p.x) * (particle->posit.p.x - area->posit.p.x);
		float y = (particle->posit.p.y - area->posit.p.y) * (particle->posit.p.y - area->posit.p.y);
		float z = (particle->posit.p.z - area->posit.p.z) * (particle->posit.p.z - area->posit.p.z);

		//ponerlo sin sqrt
		if (x + y + z < 400||iswhirl) {


			Vector3 pVel = particle->veloc;
			Vector3 resVel = pVel-_windir;

			Vector3 force = k1 * resVel+ k2 * resVel.normalize() * resVel;
			if(!iswhirl)
			particle->addForce(force);
			else {
				force.y = 0;
				particle->addForce(force / 100);
			}
		}

	}
	

protected:
	Particle* area;
	Vector3 _windir;
	float k1, k2;
	bool iswhirl = false;
};