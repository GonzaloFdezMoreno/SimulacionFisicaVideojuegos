#pragma once
#include "SpringForceGen.h"
#include "core.hpp"

class AnchorForceGen : public SpringForceGen {
public:
	AnchorForceGen(double k, double rest_length,const Vector3& pAnchor ):SpringForceGen(k,rest_length,nullptr) {
		
		fijo = new Particle(pAnchor, { 0,0,0 }, 1, {0,0,0},{0,0,0,1},6,0);
	}
	~AnchorForceGen() { delete fijo; }

	virtual void updateForce(Particle* p) {
		Vector3 force = part->posit.p - p->posit.p;

		const float length = force.normalize();
		const float deltaX = length - rlen;

		force *= deltaX * _k;

		p->addForce(force);

	}

	inline void setK(double k) { _k = k; }

protected:
	
	Particle* fijo;
	
};