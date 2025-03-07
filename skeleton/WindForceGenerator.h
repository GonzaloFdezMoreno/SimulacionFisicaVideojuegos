#pragma once

#include "ForceGenerator.h"
#include "core.hpp"
#include <list>

class WindForceGenerator : public ForceGenerator {
public:
	WindForceGenerator(const Vector3& w,float ka,float kb,int rad):_windir(w),k1(ka),k2(kb) {
		rd = rad;
		area = new Particle({0,40,0}, {0,0,0}, 0, {0,0,0}, {0,0,0,0.0}, rd, 0,false,0);
		areaL.push_back(area);
	}
	~WindForceGenerator() { delete area; }
	virtual void updateForce(Particle* particle, double t) {
		if (fabs(particle->inv_mass) < 1e-10) return;


		float x = (particle->posit.p.x - area->posit.p.x) * (particle->posit.p.x - area->posit.p.x);
		float y = (particle->posit.p.y - area->posit.p.y) * (particle->posit.p.y - area->posit.p.y);
		float z = (particle->posit.p.z - area->posit.p.z) * (particle->posit.p.z - area->posit.p.z);

		//ponerlo sin sqrt
		if (x + y + z < rd*rd||iswhirl) {


			Vector3 pVel = particle->veloc;
			Vector3 resVel = pVel-_windir;

			Vector3 force = k1 * resVel+ k2 * resVel.normalize() * resVel;
			if(!iswhirl)
			particle->addForce(force);
			else {
				force.y = 0;
				particle->addForce(force / 10);
			}
		}

	}

	virtual void updateObjectForce(physx::PxRigidDynamic* obj, double t) {
		if (fabs(obj->getInvMass()) < 1e-10)
			return;
		float x = (obj->getGlobalPose().p.x - area->posit.p.x) * (obj->getGlobalPose().p.x - area->posit.p.x);
		float y = (obj->getGlobalPose().p.y - area->posit.p.y) * (obj->getGlobalPose().p.y - area->posit.p.y);
		float z = (obj->getGlobalPose().p.z - area->posit.p.z) * (obj->getGlobalPose().p.z - area->posit.p.z);
		
		//ponerlo sin sqrt
		if (x + y + z < rd*rd || iswhirl) {

			
			Vector3 pVel = obj->getLinearVelocity();
			Vector3 resVel = pVel - _windir;

			Vector3 force = k1 * resVel + k2 * resVel.normalize() * resVel;
			if (!iswhirl)
				obj->addForce(force);
			else {
				force.y = 0;
				obj->addForce(force / 100);
			}
		}
	}

	void eraseArea() {
		for (auto ar=areaL.begin(); ar != areaL.end();) {
			delete* ar;
			ar = areaL.erase(ar);
		}
	}


protected:
	Particle* area;

	std::list<Particle*> areaL;
	Vector3 _windir;
	float k1, k2;
	bool iswhirl = false;
	int rd;
};