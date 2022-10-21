#include "Firework.h"


Firework::Firework(Vector3 pos, Vector3 vel, float damping, Vector3 accelerate, Vector4 color, int tam):Particle(pos,vel,damping,accelerate,color,tam) {

}

Firework::~Firework() {

}


void Firework::update(double t){

}

std::list<Particle*> Firework::explode() {

}

