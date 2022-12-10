#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class ExplosionForceGenerator : public ForceGenerator {
public:
	ExplosionForceGenerator(const Vector3& pos, float rad,double con) : pos_(pos), rd(rad),kon(con) {
		expArea = new Particle(pos, { 0,0,0 }, 0, { 0,0,0 }, { 0,0,0,0.2 },rd, 0,false);
		expArea = new Particle(pos, { 0,0,0 }, 0, { 0,0,0 }, { 0,0,0,0.2 },rd, 0,false);
		
	}
	~ExplosionForceGenerator() { delete expArea; }
	virtual void updateForce(Particle* particle, double t) {
		if (fabs(particle->inv_mass) < 1e-10) return;

		float x = (particle->posit.p.x - expArea->posit.p.x) * (particle->posit.p.x - expArea->posit.p.x);
		float y = (particle->posit.p.y - expArea->posit.p.y) * (particle->posit.p.y - expArea->posit.p.y);
		float z = (particle->posit.p.z - expArea->posit.p.z) * (particle->posit.p.z - expArea->posit.p.z);
		
		Vector3 force = (particle->posit.p - expArea->posit.p)*exp(-t/kon);

		//hacerlo sin sqrt
		if (x + y + z < rd*rd) {
			//affected = true;
			
			particle->addForce((force * force.normalize()));
		}
		

		//la vuelta
	/*	if(affected&& sqrt(x + y + z) > rd) {
			
			particle->addForce(-(force / sqrt(x + y + z)));
		}*/

		
	}

	virtual void updateObjectForce(physx::PxRigidDynamic* obj, double t) {
		if (fabs(obj->getInvMass()) < 1e-10)
			return;
		float x = (obj->getGlobalPose().p.x - expArea->posit.p.x) * (obj->getGlobalPose().p.x - expArea->posit.p.x);
		float y = (obj->getGlobalPose().p.y - expArea->posit.p.y) * (obj->getGlobalPose().p.y - expArea->posit.p.y);
		float z = (obj->getGlobalPose().p.z - expArea->posit.p.z) * (obj->getGlobalPose().p.z - expArea->posit.p.z);

		Vector3 force = (obj->getGlobalPose().p - expArea->posit.p) * exp(-t / kon);

		//hacerlo sin sqrt
		if (x + y + z < rd * rd) {
			//affected = true;

			obj->addForce((force * force.normalize()));
		}
	}


protected:

	Particle* expArea;
	float tim = 0.0f;
	Vector3 pos_;
	float rd;
	double kon;
	bool affected = false;
};
