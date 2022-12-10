#pragma once

#include "ForceGenerator.h"
#include "core.hpp"
#include "ParticleForceRegistry.h"

class GravityForceGenerator : public ForceGenerator {
public: 
	GravityForceGenerator(const Vector3& g) {
		_gravity = g;
	}
	~GravityForceGenerator(){}
	virtual void updateForce(Particle* particle, double t) {
		if (fabs(particle->inv_mass) < 1e-10)
			return;
			
			//particle->posit = physx::PxTransform(particle->posit.p.x + particle->veloc.x * t, particle->posit.p.y + particle->veloc.y * t, particle->posit.p.z + particle->veloc.z * t);
			////con damping

			//particle->veloc += _gravity * t;
			//particle->veloc *= pow(particle->damp, t);
		particle->addForce(_gravity*particle->masa);
		
	}
	virtual void updateObjectForce(physx::PxRigidDynamic* obj, double t) {
		if (fabs(obj->getInvMass()) < 1e-10)
			return;

		
		auto a = obj->getMass();
		
		obj->addForce(_gravity * a);

	}

	//inline void setGravity(Vector3 g) { _gravity = g; }
	
protected:
	Vector3 _gravity;
	ParticleForceRegistry* reg;
};