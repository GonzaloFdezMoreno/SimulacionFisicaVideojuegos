#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include <list>



class RigidBody {
public:
	//RigidBody(physx::PxPhysics* phy, physx::PxScene* scene,Vector3 pos,physx::PxGeometry forma) {
	//RigidBody(physx::PxRigidDynamic* object,Vector3 pos,physx::PxGeometry forma) {
	RigidBody(physx::PxRigidDynamic* object,Vector4 color,float formtype) {
	
		//obj = phy->createRigidDynamic(physx::PxTransform(pos));
		timeAlive = 0;
		obj = object;
		
		if (formtype <= 1) {
			physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(3));
			obj->attachShape(*shape);
			item = new RenderItem(shape, obj, { color });
		}
		else {
			physx::PxShape* shape = CreateShape(physx::PxBoxGeometry(2,2,2));
			obj->attachShape(*shape);
			item = new RenderItem(shape, obj, {color});
		}
		
		
		
		
		
		//scene->addActor(*obj);
	}
	~RigidBody() {
		DeregisterRenderItem(item);

		item = nullptr;
	}
	bool inTime() {
		return timeAlive<500;
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