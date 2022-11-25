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

	}

	inline void setK(double k) { _k = k; }

protected:
	double _k;
	Particle* part;
	double rlen;
};