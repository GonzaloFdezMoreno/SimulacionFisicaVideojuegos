#pragma once

#include "WindForceGenerator.h"
#include "core.hpp"

class WhirlpoolForceGenerator : public WindForceGenerator {
public:
	WhirlpoolForceGenerator(float k1, float k2, const Vector3& pos,float k0) :WindForceGenerator({0,0,0}, k1, k2),
		poscentro(pos),kf(k0)
	{
		
	}
	~WhirlpoolForceGenerator() {  }
	virtual void updateForce(Particle* particle, double t) {
		if (fabs(particle->inv_mass) < 1e-10) return;
		iswhirl = true;

		auto x = kf* -(particle->posit.p.z - poscentro.z);
		auto y = -2 -(particle->posit.p.y - poscentro.y);
		auto z = kf* (particle->posit.p.x - poscentro.x);
		_windir = Vector3(x, y, z);
		
		WindForceGenerator::updateForce(particle, t);

	}


protected:
	
	Vector3 poscentro;
	float kf;
	
};
