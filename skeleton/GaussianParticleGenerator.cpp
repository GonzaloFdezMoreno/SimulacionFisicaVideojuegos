#include "GaussianParticleGenerator.h"



GaussianParticleGenerator::GaussianParticleGenerator(Vector3 pos,Vector3 vel):ParticleGenerator(pos,vel) {

	 std_dev_pos=pos;
	 std_dev_vel=vel;

}
GaussianParticleGenerator::~GaussianParticleGenerator() {

}

std::list<Particle*> GaussianParticleGenerator::generateParticles() {
	std::list<Particle*> lPart;

	float rx = rand() % 50;
	////float ry = rand() % 4 + 1;
	float rz = rand() % 50;

	/*float vx = rand() % 10;
	float vy = rand() % 10;
	float vz = rand() % 10;*/

	auto vx = std::normal_distribution<float>{ 5, 3 }; 
	auto vy = std::normal_distribution<float>{ 10, 1 };
	auto vz = std::normal_distribution<float>{ 5, 2 };

	float negx = rand() % 10 + 1;
	float negy = rand() % 10 + 1;
	float negz = rand() % 10 + 1;


	float rmass = rand() % 7 + 1;
	float rtam = rand() % 3 + 1;

	//int tamrnd = rand() % 4 + 1;


	//Vector3 velc = { vx(rnd),vy(rnd),vz(rnd) };
	Vector3 velc = { vx(rnd),vy(rnd),vz(rnd)};

	if (negx < 5) {
		velc.x = -velc.x;
	}
	/*else if (negy < 5) {
		velc.y = -velc.y;
	}*/
	else if (negz < 5) {
		velc.z = -velc.z;
	}

	Particle* part = new Particle( std_dev_pos ,velc*2, 1, {0,0,0}, {0,0.2,0.7,1}, rtam/2,rmass,false,500);
	lPart.push_back(part);


	return lPart;

}

std::list<physx::PxRigidDynamic*> GaussianParticleGenerator::generateObjects(physx::PxPhysics* phy, physx::PxScene* scene) {
	//std::list<RigidBody*> lobj;
	std::list<physx::PxRigidDynamic*> lobj;
	//auto vx = std::normal_distribution<float>{ 1, 5 };
	//auto vy = std::normal_distribution<float>{ 2, 2 };
	////auto vy = 0.0f;
	//auto vz = std::normal_distribution<float>{ 1, 1 };
	//Vector3 velc = { vx(rnd),vy(rnd),vz(rnd) };
	////RigidBody* obj = new RigidBody(phy, scene, { rx,50,rz }, physx::PxSphereGeometry(5));
	////RigidBody* object = new RigidBody(phy->createRigidDynamic(physx::PxTransform({ rx,50,rz })), { rx,50,rz }, physx::PxSphereGeometry(5));
	//
	//physx::PxRigidDynamic* obj = phy->createRigidDynamic(physx::PxTransform(velc));
	//physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(5));
	//obj->attachShape(*shape);
	//RenderItem* item = new RenderItem(shape, obj, { 0.5,0.8,1,1 });

	//scene->addActor(*obj);
	////scene->addActor(*object->obj);
	//lobj.push_back(obj);



	return lobj;
}