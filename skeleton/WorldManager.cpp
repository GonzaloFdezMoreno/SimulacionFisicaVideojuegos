#include "WorldManager.h"

WorldManager::WorldManager(int nobj, physx::PxPhysics* phys, physx::PxScene* sc) {
	nob = nobj;
	phy = phys;
	scene = sc;
	uPG = new UniformParticleGenerator({ 2,2,0 }, { 1,2,1 });
	_particles_generators.push_back(uPG);

	srand(time(NULL));
}


WorldManager::~WorldManager() {

}

void WorldManager::update(double t) {
	if (_objects.size() < nob) {
		
		std::list<physx::PxRigidDynamic*> odyn = uPG->generateObjects(phy, scene);
		for (auto pl : odyn) {
			_objects.push_back(pl);

		}
	}
}