#pragma once
#include <map>
#include "core.hpp"
#include "ForceGenerator.h"

typedef std::pair<ForceGenerator*, physx::PxRigidDynamic*> frPairOb;



class ObjectForceRegistry:public std::multimap<ForceGenerator*, physx::PxRigidDynamic*> {

public:
	void updateObjectsForces(double t) {
		for (auto it = begin(); it != end(); it++) {
			it->first->updateObjectForce(it->second, t);
		}
	}

	void addRegistry(ForceGenerator* fg, physx::PxRigidDynamic* p) {

		insert({ fg, p });

	}

	void deleteParticleRegistry(physx::PxRigidDynamic* p) {


		auto it = begin();
		for (auto it = begin(); it != end();) {
			if (it->second == p) {
				it = erase(it);
			}
			else {
				++it;
			}
		}
	}

};