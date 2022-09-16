#include "Particle.h"

Particle::Particle(Vector3 pos,Vector3 vel) {
	veloc = vel;
	posit = physx::PxTransform(pos.x, pos.y, pos.z);
	renderItemPart = new RenderItem(CreateShape(physx::PxCapsuleGeometry(2, 5)), &posit, { 0,0,1,1 });

}

Particle::~Particle() {
	renderItemPart = nullptr;
	DeregisterRenderItem(renderItemPart);
	
}
void Particle::integrate(double t) {
	posit = physx::PxTransform(posit.p.x + veloc.x * t, posit.p.y + veloc.y * t, posit.p.z + veloc.z * t);
}