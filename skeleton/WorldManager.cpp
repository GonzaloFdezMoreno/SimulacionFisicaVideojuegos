#include "WorldManager.h"

WorldManager::WorldManager(int nobj, physx::PxPhysics* phys, physx::PxScene* sc) {
	nob = nobj;
	phy = phys;
	scene = sc;
	uPG = new UniformParticleGenerator({ 2,2,0 }, { 1,2,1 });
	_particles_generators.push_back(uPG);
	regforobj = new ObjectForceRegistry();
	srand(time(NULL));

	//gforceGen = new GravityForceGenerator({ 0,-9.8,0 });
	//whForceGen = new WhirlpoolForceGenerator(1, 0.5, { 20,100,20 }, 0.4);
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
				regforobj->addRegistry(expForceGen2, (*ob)->obj);
				regforobj->addRegistry(expForceGen3, (*ob)->obj);
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

	if (points >= 5 && !diana2creada) {
		for (auto di = diana.begin(); di != diana.end();) {

			delete* di;
			di = diana.erase(di);
		}
		diana1destruida = true;

		createDiana2();
		diana2creada = true;
		
	}

	else if (points >= 7 && !diana3creada) {
		for (auto di = diana.begin(); di != diana.end();) {

			delete* di;
			di = diana.erase(di);
			
		}
		diana2destruida = true;

		createDiana3();
		diana3creada = true;
	}

	else if (points >= 8 && !diana4creada) {
		for (auto di = diana.begin(); di != diana.end();) {

			delete* di;
			di = diana.erase(di);
		}
		diana3destruida = true;

		createDiana4();
		diana4creada = true;
	}

	else if (points >= 9 && !diana5creada) {
		for (auto di = diana.begin(); di != diana.end();) {

			delete* di;
			di = diana.erase(di);
		}
		expForceGen->eraseArea();
		expForceGen2->eraseArea();
		expForceGen3->eraseArea();

		diana4destruida = true;

		getexplosion = false;
		createDiana5();
		diana5creada = true;
	}
	else if (points >= 10) {
		for (auto di = diana.begin(); di != diana.end();) {

			delete* di;
			di = diana.erase(di);
		}

		wforceGen->eraseArea();
		diana5destruida = true;
	}

	//if (_objects.size() < nob) {
	//	//if (create) {
	//		std::list<physx::PxRigidDynamic*> odyn = uPG->generateObjects(phy, scene);
	//		//std::list<RigidBody*> odyn = uPG->generateObjects(phy, scene);
	//		for (auto pl : odyn) {
	//			//_rigidobjects.push_back(pl);
	//			auto rr = std::normal_distribution<float>{ 1, 1 };
	//			auto rg = std::normal_distribution<float>{ 1, 1 };
	//			auto rb = std::normal_distribution<float>{ 1, 1 };
	//			auto rf = std::normal_distribution<float>{ 1, 1 };
	//			_objects.push_back(new RigidBody(pl, {rr(rnd),rg(rnd),rb(rnd),1}, rf(rnd)));
	//			scene->addActor((*pl));
	//		}
	//		//create = false;
	//	/*}
	//	else {
	//		if (delay < 200) {
	//			delay++;
	//		}
	//		else {
	//			delay = 0;
	//			create = true;
	//		}
	//	}*/
	//}

	for (auto ob = _objects.begin(); ob != _objects.end();) {
		if ((*ob)->obj->getGlobalPose().p.y >= 10) {
			if ((*ob)->inTime()) {
				(*ob)->addTime();
				ob++;
			}
			else {

				delete* ob;
				ob = _objects.erase(ob);
			}


		}
		else {


			delete* ob;
			ob = _objects.erase(ob);
		}


	}
	
}


void WorldManager::createExplosionForce() {

	expForceGen = new ExplosionForceGenerator({ 0,0,0 }, 50, 2);
}

void WorldManager::createwindAreaForce() {
	//wforceGen = new WindForceGenerator({ 5,-5,5 }, 0.5, 0);
}

void WorldManager::addToList(RigidBody* rigid) {
	_objects.push_back(rigid);
}

//crear aqui las dianas y quitarlas/ponerlas con los puntos a través de una lista
void WorldManager::createDiana() {
	physx::PxRigidStatic* outer = phy->createRigidStatic(physx::PxTransform({ 0,100,-30 }));
	outer->setName("baja");

	StaticRigidBody* fue = new StaticRigidBody(outer, { 0.0,0.5,0.5,1 }, 2, 0, { 20,20,0.2 });

	////PxRigidDynamic* wall = gPhysics->createRigidDynamic(PxTransform({ 10,30,-30}));
	//PxShape* shapeOuter = CreateShape(PxBoxGeometry(20, 20, 0.2));
	//outer->attachShape(*shapeOuter);
	//item = new RenderItem(shapeOuter, outer, { 0,0.5,0.5,1 });
	scene->addActor(*outer);
	diana.push_back(fue);


	physx::PxRigidStatic* midA = phy->createRigidStatic(physx::PxTransform({ 0,100,-30 }));
	midA->setName("media-baja");
	StaticRigidBody* mA = new StaticRigidBody(midA, { 0.0,0,0.8,1 }, 2, 0, { 15,15,0.25 });
	//PxRigidDynamic* wall = gPhysics->createRigidDynamic(PxTransform({ 10,30,-30}));
	/*PxShape* shapeMidA = CreateShape(PxBoxGeometry(15, 15, 0.25));
	midA->attachShape(*shapeMidA);
	item = new RenderItem(shapeMidA, midA, { 0,0,0.8,1 });*/
	scene->addActor(*midA);
	diana.push_back(mA);

	physx::PxRigidStatic* midB = phy->createRigidStatic(physx::PxTransform({ 0,100,-30 }));
	midB->setName("media");
	StaticRigidBody* mB = new StaticRigidBody(midB, { 0.0,0.8,0.0,1 }, 2, 0, { 10,10,0.3 });
	//PxRigidDynamic* wall = gPhysics->createRigidDynamic(PxTransform({ 10,30,-30}));
	/*PxShape* shapeMidB = CreateShape(PxBoxGeometry(10, 10, 0.3));
	midB->attachShape(*shapeMidB);
	item = new RenderItem(shapeMidB, midB, { 0,0.8,0,1 });*/
	scene->addActor(*midB);
	diana.push_back(mB);

	physx::PxRigidStatic* midC = phy->createRigidStatic(physx::PxTransform({ 0,100,-30 }));
	midC->setName("media-alta");
	StaticRigidBody* mC = new StaticRigidBody(midC, { 0.8,0.8,0,1 }, 2, 0, { 5,5,0.35 });

	//PxRigidDynamic* wall = gPhysics->createRigidDynamic(PxTransform({ 10,30,-30}));
	/*PxShape* shapeMidC = CreateShape(PxBoxGeometry(5, 5, 0.35));
	midC->attachShape(*shapeMidC);
	item = new RenderItem(shapeMidC, midC, { 0.8,0.8,0,1 });*/
	scene->addActor(*midC);
	diana.push_back(mC);

	physx::PxRigidStatic* center = phy->createRigidStatic(physx::PxTransform({ 0,100,-30 }));
	center->setName("alta");
	StaticRigidBody* cen = new StaticRigidBody(center, { 1,0,0,1 }, 2, 0, { 2,2,0.4 });

	//PxRigidDynamic* wall = gPhysics->createRigidDynamic(PxTransform({ 10,30,-30}));
	/*PxShape* shapeCenter = CreateShape(PxBoxGeometry(2, 2, 0.4));
	center->attachShape(*shapeCenter);
	item = new RenderItem(shapeCenter, center, { 1,0,0,1 });*/
	scene->addActor(*center);
	diana.push_back(cen);
}


void WorldManager::createDiana2() {
	physx::PxRigidStatic* diaB2 = phy->createRigidStatic(physx::PxTransform({ 50,70,30 }));
	diaB2->setName("baja2");
	//PxRigidDynamic* wall = gPhysics->createRigidDynamic(PxTransform({ 10,30,-30}));
	StaticRigidBody* out2 = new StaticRigidBody(diaB2, { 1,1,0,1 }, 2, 0, { 5,5,0.2 });
	
	scene->addActor(*diaB2);
	diana.push_back(out2);

	physx::PxRigidStatic* diaM2 = phy->createRigidStatic(physx::PxTransform({ 50,70,30 }));
	diaM2->setName("media2");
	//PxRigidDynamic* wall = gPhysics->createRigidDynamic(PxTransform({ 10,30,-30}));
	StaticRigidBody* med2 = new StaticRigidBody(diaM2, { 1,0,0,1 }, 2, 0, { 3.5,3.5,0.3 });
	scene->addActor(*diaM2);
	diana.push_back(med2);

	physx::PxRigidStatic* diaA2 = phy->createRigidStatic(physx::PxTransform({ 50,70,30 }));
	diaA2->setName("alta2");
	//PxRigidDynamic* wall = gPhysics->createRigidDynamic(PxTransform({ 10,30,-30}));
	StaticRigidBody* cen2 = new StaticRigidBody(diaA2, { 1,0,1,1 }, 2, 0, { 2,2,0.4 });
	scene->addActor(*diaA2);
	diana.push_back(cen2);
	

	
}

void WorldManager::createDiana3() {
	
	physx::PxRigidStatic* diaA3 = phy->createRigidStatic(physx::PxTransform({ -50,50,-70 }));
	diaA3->setName("alta3");
	//PxRigidDynamic* wall = gPhysics->createRigidDynamic(PxTransform({ 10,30,-30}));
	StaticRigidBody* cen3 = new StaticRigidBody(diaA3, { 0.3,0.2,0.5,1 }, 2, 0, { 1.5,1.5,0.4 });
	scene->addActor(*diaA3);
	diana.push_back(cen3);


	
}

void WorldManager::createDiana4() {
	getexplosion = true;
	expForceGen = new ExplosionForceGenerator({ -10,62,-30 }, 10, 0.5);
	expForceGen2 = new ExplosionForceGenerator({ -20,80,-35 }, 10, 0.5);
	expForceGen3 = new ExplosionForceGenerator({ -30,63,-20 }, 10, 0.5);

	physx::PxRigidStatic* diaA4 = phy->createRigidStatic(physx::PxTransform({ -20,70,-40 }));
	diaA4->setName("alta4");
	//PxRigidDynamic* wall = gPhysics->createRigidDynamic(PxTransform({ 10,30,-30}));
	StaticRigidBody* cen4 = new StaticRigidBody(diaA4, { 0.3,0.2,0.5,1 }, 2, 0, { 2.5,2.5,0.4 });
	scene->addActor(*diaA4);
	diana.push_back(cen4);


	
}

void WorldManager::createDiana5() {
	getwind = true;
	wforceGen = new WindForceGenerator({ 1000,500,1000 }, 0.5, 0, 70);

	physx::PxRigidStatic* diaA5 = phy->createRigidStatic(physx::PxTransform({ -20,40,-20 }));
	diaA5->setName("alta5");
	//PxRigidDynamic* wall = gPhysics->createRigidDynamic(PxTransform({ 10,30,-30}));
	StaticRigidBody* cen5 = new StaticRigidBody(diaA5, { 0.3,0.2,0.5,1 }, 2, 0, { 2,0.4,2 });
	scene->addActor(*diaA5);
	diana.push_back(cen5);


	
}