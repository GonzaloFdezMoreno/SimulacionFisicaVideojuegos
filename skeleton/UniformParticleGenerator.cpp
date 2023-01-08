#include "UniformParticleGenerator.h"


UniformParticleGenerator::UniformParticleGenerator(Vector3 vel,Vector3 pos):ParticleGenerator(pos,vel) {

	_vel_width = vel;


}
UniformParticleGenerator::~UniformParticleGenerator() {

} 

std::list<Particle*> UniformParticleGenerator::generateParticles() {
	//Crear lista nueva desde aqui
	std::list<Particle*> lPart;
	float rx = rand() % 100;
	//float ry = rand() % 50;
	float rz = rand() % 50;
	int ini = rx;
	if (ini % 2 == 0) {
		rx -= (rx * 2);
	}

	PAgua* part = new PAgua({rx,100,-145}, _vel_width, 1, { 0,-7,0 }, { 0,0.6,1,1 }, 1);
	lPart.push_back(part);
	
	return lPart;
}

std::list<physx::PxRigidDynamic*> UniformParticleGenerator::generateObjects(physx::PxPhysics* phy, physx::PxScene* scene) {
	//Crear lista nueva desde aqui
	std::list<physx::PxRigidDynamic*> lobj;
	float rx = rand() % 50;
	//float ry = rand() % 50;
	float rz = rand() % 50;

	physx::PxRigidDynamic* obj = phy->createRigidDynamic(physx::PxTransform({ rx,50,rz }));
	//physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(5));
	//obj->attachShape(*shape);
	//RenderItem* item = new RenderItem(shape, obj, { 0.5,0.8,1,1 });
	//scene->addActor(*obj);;
	lobj.push_back(obj);

	

	return lobj;
}


