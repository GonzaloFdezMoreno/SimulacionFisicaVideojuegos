#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include <list>



class RigidBody {
public:
	//RigidBody(physx::PxPhysics* phy, physx::PxScene* scene,Vector3 pos,physx::PxGeometry forma) {
	//RigidBody(physx::PxRigidDynamic* object,Vector3 pos,physx::PxGeometry forma) {
	RigidBody(physx::PxRigidDynamic* object) {
	
		//obj = phy->createRigidDynamic(physx::PxTransform(pos));
		timeAlive = 0;
		obj = object;
		physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(5));
		obj->attachShape(*shape);
		item = new RenderItem(shape, obj, { 0.5,0.8,1,1 });
		//scene->addActor(*obj);
	}
	~RigidBody() {
		DeregisterRenderItem(item);

		item = nullptr;
	}
	bool inTime() {
		return timeAlive<4000;
	}
	void addTime() {
		timeAlive++;
	}

	bool die = false;
	
	
	//float timeToLive = 400;

	physx::PxRigidDynamic* obj = nullptr;
	RenderItem* item = nullptr;
	

protected:


	RenderItem* renderItemPart;

	float timeAlive;
	
};