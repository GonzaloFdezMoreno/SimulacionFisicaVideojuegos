#pragma once

#include <map>
#include "ForceGenerator.h"

typedef std::pair<ForceGenerator*, Particle*> frPair;

class ParticleForceRegistry :public std::multimap<ForceGenerator*, Particle*> {
public:
	void updateForces(double t) {
		for (auto it = begin(); it != end(); it++) {
			it->first->updateForce(it->second, t);
		}
	}

	void addRegistry(ForceGenerator* fg,Particle* p){
		/*auto it = begin();
		while (it->first != nullptr) {
			it++;
		}
		it->first = fg;
		it->second = p;
		insert(it);*/
			
	}

	void deleteParticleRegistry(Particle* p) {
		auto it = begin();
		while (it->second != p && it != end()) {
			it++;
		}
		if (it->second == p) {
			erase(it);
		}
	}
};