#include "WorldManager.h"

WorldManager::WorldManager(int nobj, physx::PxPhysics* phys, physx::PxScene* sc) {
	nob = nobj;
	phy = phys;
	scene = sc;
	uPG = new UniformParticleGenerator({ 2,2,0 }, { 1,2,1 });
	_particles_generators.push_back(uPG);
	regforobj = new ObjectForceRegistry();
	srand(time(NULL));

	gforceGen = new GravityForceGenerator({ 0,-9.8,0 });
	whForceGen = new WhirlpoolForceGenerator(1, 0.5, { 20,100,20 }, 0.4);
}


WorldManager::~WorldManager() {

}

void WorldManager::update(double t) {
	
	regforobj->updateObjectsForces(t);

	for (auto ob = _objects.begin(); ob != _objects.end();) {

		if (getgrav) {
			regforobj->addRegistry(gforceGen, (*ob)->obj);
		}
		if (getwind) {
			if (wforceGen != nullptr)
				regforobj->addRegistry(wforceGen, (*ob)->obj);
		}
		if (getexplosion) {
			if (expForceGen != nullptr)
				regforobj->addRegistry(expForceGen, (*ob)->obj);
		}
		if (getWhirl) {
			regforobj->addRegistry(whForceGen, (*ob)->obj);
		}
		
		if ((*ob)->inTime()) {
			(*ob)->addTime();
			ob++;
		}
		else {
			regforobj->deleteParticleRegistry((*ob)->obj);
			delete* ob;
			ob = _objects.erase(ob);
		}

		
	}

	if (_objects.size() < nob) {
		//if (create) {
			std::list<physx::PxRigidDynamic*> odyn = uPG->generateObjects(phy, scene);
			//std::list<RigidBody*> odyn = uPG->generateObjects(phy, scene);
			for (auto pl : odyn) {
				//_rigidobjects.push_back(pl);
				auto rr = std::normal_distribution<float>{ 1, 1 };
				auto rg = std::normal_distribution<float>{ 1, 1 };
				auto rb = std::normal_distribution<float>{ 1, 1 };
				auto rf = std::normal_distribution<float>{ 1, 1 };
				_objects.push_back(new RigidBody(pl, {rr(rnd),rg(rnd),rb(rnd),1}, rf(rnd)));
				scene->addActor((*pl));
			}
			//create = false;
		/*}
		else {
			if (delay < 200) {
				delay++;
			}
			else {
				delay = 0;
				create = true;
			}
		}*/
	}
	
}


void WorldManager::createExplosionForce() {

	expForceGen = new ExplosionForceGenerator({ 0,0,0 }, 50, 2);
}

void WorldManager::createwindAreaForce() {
	wforceGen = new WindForceGenerator({ 5,-5,5 }, 0.5, 0);
}