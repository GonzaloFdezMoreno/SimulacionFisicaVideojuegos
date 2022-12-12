#include "FireworkGenerator.h"



FireworkGenerator::FireworkGenerator(Vector3 pos, Vector3 vel) :ParticleGenerator(pos,vel) {

	std_dev_pos = pos;
	std_dev_vel = vel;

}
FireworkGenerator::~FireworkGenerator() {

}

//std::list<Firework*> FireworkGenerator::generateParticles() {
//	std::list<Firework*> lPart;
//	Firework* part = new Firework({ std_dev_pos }, { std_dev_vel }, 0.7, { 0,0,0 }, { 0,0.6,1,1 }, 3);
//	lPart.push_back(part);
//
//
//	return lPart;
//
//}


std::list<Particle*> FireworkGenerator::generateParticles() {
	std::list<Particle*> lPart;
	Firework* part = new Firework({ std_dev_pos }, { std_dev_vel }, 0.7, { 0,0,0 }, { 0,0.6,1,1 }, 3);
	lPart.push_back(part);


	return lPart;

}

std::list<physx::PxRigidDynamic*> FireworkGenerator::generateObjects(physx::PxPhysics* phy, physx::PxScene* scene) {
	//std::list<RigidBody*> lobj;
	std::list<physx::PxRigidDynamic*> lobj;
	float rx = rand() % 50;
	//float ry = rand() % 50;
	float rz = rand() % 50;

	//RigidBody* obj = new RigidBody(phy, scene, { rx,50,rz }, physx::PxSphereGeometry(5));
	physx::PxRigidDynamic* obj = phy->createRigidDynamic(physx::PxTransform({ rx,50,rz }));
	physx::PxShape* shape = CreateShape(physx::PxBoxGeometry(100, 0.1, 100));
	obj->attachShape(*shape);
	RenderItem* item = new RenderItem(shape, obj, { 0.5,0.8,1,1 });
	scene->addActor(*obj);;
	lobj.push_back(obj);



	return lobj;
}