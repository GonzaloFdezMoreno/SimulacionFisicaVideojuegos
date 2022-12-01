#pragma once
#include "SpringForceGen.h"
#include "core.hpp"

class AnchorForceGen : public SpringForceGen {
public:
	AnchorForceGen(double k, double rest_length,const Vector3& pAnchor ):SpringForceGen(k,rest_length,nullptr) {
		
		part = new Particle(pAnchor, { 0,0,0 }, 1, {0,0,0},{0,0,0,1},6,0);


	}
	~AnchorForceGen() { delete part; }

	inline void setK(double k) { _k = k; }

protected:
	
	//Particle* fijo;
	
	
};