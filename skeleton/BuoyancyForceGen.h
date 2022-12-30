#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class BuoyancyForceGen : public ForceGenerator {
public:
	BuoyancyForceGen(float h, float v, float den) {
		_height= h;
		_volume = v;
		_liquid = den;

		parliq = new Particle({70,20,-70}, {0,0,0}, 1, {0,0,0}, {1,0,0,0.5}, _height, 0, true,0);
	}
	~BuoyancyForceGen() {}

	virtual void updateForce(Particle* p, double t) {

		float h = p->posit.p.y;
		float h0 = parliq->posit.p.y;

		Vector3 fl(0, 0, 0);
		float in = 0.0f;
		if (h - h0 > _height * 0.5) {
			in = 0.0f;
		}
		else if (h - h0 > _height * 0.5) {
			in = 1.0f;
		}
		else {
			in = (h0 - h) / _height + 0.5;
		}
		fl.y = _liquid * _volume * in * 9.8;
		p->addForce(fl);
	}

	virtual void updateObjectForce(physx::PxRigidDynamic* obj, double t) {

		float h = obj->getGlobalPose().p.y;
		float h0 = parliq->posit.p.y;

		Vector3 fl(0, 0, 0);
		float in = 0.0f;
		if (h - h0 > _height * 0.5) {
			in = 0.0f;
		}
		else if (h - h0 > _height * 0.5) {
			in = 1.0f;
		}
		else {
			in = (h0 - h) / _height + 0.5;
		}
		fl.y = _liquid * _volume * in * 9.8;
		obj->addForce(fl);
	}

protected:
	float _height;
	float _volume;
	float _liquid;
	float _gravity=9.8f;

	Particle* parliq;
	
};