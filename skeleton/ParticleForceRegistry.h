#pragma once

#include <map>
#include "ForceGenerator.h"

typedef std::pair<ForceGenerator*, Particle*> frPair;

class ParticleForceRegistry :public std::multimap<ForceGenerator*, Particle*> {
public:
	//afecta a las áreas solo
	
	ParticleForceRegistry() {}
	~ParticleForceRegistry(){}

	void updateForces(double t) {
		for (auto it = begin(); it != end(); it++) {
			it->first->updateForce(it->second, t);
		}
	}

	

	void addRegistry(ForceGenerator* fg,Particle* p){
		
		insert({ fg, p });
		
	}

	void deleteParticleRegistry(Particle* p) {
		

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