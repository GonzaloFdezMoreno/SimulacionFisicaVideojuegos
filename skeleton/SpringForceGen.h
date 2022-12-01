#pragma once
#include "ForceGenerator.h"
#include "core.hpp"

class SpringForceGen : public ForceGenerator {
public:
	SpringForceGen(double k, double rest_length, Particle* par0) {
		_k = k;
		rlen = rest_length;
		part = par0;
	}
	~SpringForceGen(){}

	virtual void updateForce(Particle* p) {
		Vector3 force = part->posit.p - p->posit.p;

		const float length = force.normalize();
		const float deltaX = length - rlen;

		force *= deltaX * _k;

		p->addForce(force);

	}

	inline void setK(double k) { _k = k; }

protected:
	double _k;
	Particle* part;
	double rlen;
};