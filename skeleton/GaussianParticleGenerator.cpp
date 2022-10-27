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

	float vx = rand() % 10;
	float vy = rand() % 10;
	float vz = rand() % 10;

	/*auto vx = std::normal_distribution<float>(10,20);
	auto vy = std::normal_distribution<float>(10,2);
	auto vz = std::normal_distribution<float>(15,5);*/

	float negx = rand() % 10 + 1;
	float negy = rand() % 10 + 1;
	float negz = rand() % 10 + 1;

	//int tamrnd = rand() % 4 + 1;

	if (negx < 5) {
		vx = vx - (2 * vx);
	}
	else if (negy < 5) {
		vy = vy - (2 * vy);
	}
	else if (negz < 5) {
		vz = vz - (2 * vz);
	}
	Vector3 vel = { vx,vy,vz };

	Particle* part = new Particle({rx,20,rz} /* std_dev_pos */ , std_dev_vel, 1, {0,0,0}, {0,0.6,1,1}, 3);
	lPart.push_back(part);


	return lPart;

}