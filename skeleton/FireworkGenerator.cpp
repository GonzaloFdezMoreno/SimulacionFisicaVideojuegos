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