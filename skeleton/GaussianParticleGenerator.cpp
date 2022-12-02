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

	auto vx = std::normal_distribution<float>{ 1, 5 }; 
	auto vy = std::normal_distribution<float>{ 2, 2 };
	//auto vy = 0.0f;
	auto vz = std::normal_distribution<float>{1, 1 };

	float negx = rand() % 10 + 1;
	float negy = rand() % 10 + 1;
	float negz = rand() % 10 + 1;


	float rmass = rand() % 4 + 1;
	float rtam = rand() % 2 + 1;

	//int tamrnd = rand() % 4 + 1;


	//Vector3 velc = { vx(rnd),vy(rnd),vz(rnd) };
	Vector3 velc = { vx(rnd),vy(rnd),vz(rnd)};

	if (negx < 5) {
		velc.x = -velc.x;
	}
	else if (negy < 5) {
		velc.y = -velc.y;
	}
	else if (negz < 5) {
		velc.z = -velc.z;
	}

	Particle* part = new Particle({ rx,100,rz } /* std_dev_pos */,velc, 1, {0,0,0}, {0,0.6,1,1}, rtam,rmass,false);
	lPart.push_back(part);


	return lPart;

}