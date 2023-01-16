#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>
#include "Particle.h"
#include "Mshot.h"
#include "Plane.h"
#include "ParticleSystem.h"
#include "Firework.h"

#include "WorldManager.h"




using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

Particle* partic = NULL;
//std::vector<RigidBody*> bullets ;


Plane* plan = NULL;
ParticleSystem* psys = NULL;
//Firework* fwo = NULL;
std::vector<Firework*> fwoVec;

RenderItem* item = NULL;

WorldManager* wmg = NULL;



// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	//Añadir elementos
	//partic = new Particle({ 0,50,0 },{ -10,20,0 }, 0.9, {0,-9.8,0});
	//plan = new Plane({ 0,-100,0 }, { 0,1,0,1 });

	psys = new ParticleSystem(2);

	PxRigidStatic* suelo = gPhysics->createRigidStatic(PxTransform({ 0,0,0 }));
	PxShape* shape = CreateShape(PxBoxGeometry(100, 0.1, 100));
	suelo->attachShape(*shape);
	item = new RenderItem(shape, suelo, { 0.5,0.8,1,1 });
	gScene->addActor(*suelo);


	wmg = new WorldManager(10, gPhysics, gScene);

	wmg->createDiana();

	
	
	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);

	//for(auto b:bullets)
	//partic->integrate(t);
	//b->integrate(t);

	if(psys!=NULL)
	psys->update(t);

	wmg->update(t);

	/*for (auto ob = bullets.begin(); ob != bullets.end();) {
		if ((*ob)->obj->getGlobalPose().p.y >= 10) {
			if ((*ob)->inTime()) {
				(*ob)->addTime();
				ob++;
			}
			else {
			
			delete* ob;
			ob = bullets.erase(ob);
			}
		

		}
		else {
			

			delete* ob;
			ob = bullets.erase(ob);
		}
	
	
	}*/

	

	//mejor crear el generador de fuegos
	
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);
	PxRigidDynamic* bul;
	RigidBody* rigBul;

	switch(toupper(key))
	{
	case 'B':
		//pistola
		//bullets.push_back(new Mshot(0.4, { GetCamera()->getDir() * 250 }, { GetCamera()->getEye() }, 0.99, { 0,-0.5,0 }, {0.3,0.4,0.5,1},2));
		bul= gPhysics->createRigidDynamic(physx::PxTransform({ GetCamera()->getEye() }));
		rigBul = new RigidBody(bul, { 0.5,0.5,0.5,1 }, 0, 2);
		//bullets.push_back(rigBul);
		wmg->addToList(rigBul);

		bul->setMass(0.4);
		bul->setLinearDamping(0.5);
		gScene->addActor(*bul);
		bul->setName("bala");
		bul->setLinearVelocity(GetCamera()->getDir() * 250);
		
		
		break;
	case 'L': {
		//laser
		//bullets.push_back(new Mshot(0.1, { GetCamera()->getDir() * 1000 }, { GetCamera()->getEye() }, 0.99, { 0,0,0 },{1,0,0,1},2));
		
		break; 
	}
	case 'C':
	{
		bul = gPhysics->createRigidDynamic(physx::PxTransform({ GetCamera()->getEye() }));
		rigBul = new RigidBody(bul, { 1,0.5,0.5,1 }, 2, 3);

		//bullets.push_back(rigBul);
		wmg->addToList(rigBul);
		bul->setLinearDamping(0.8);
		bul->setMass(3);
		gScene->addActor(*bul);
		bul->setName("bala");
		bul->setLinearVelocity(GetCamera()->getDir() * 100);
		break;
	}
	case 'F':
	{
		//bfuego
		//bullets.push_back(new Mshot(1, { GetCamera()->getDir() * 100 }, {GetCamera()->getEye() }, 0.9, { 0,0.5,0 },{0.8,0.4,0,1},5));

		//fuegos artificiales
		if(psys!=NULL)
		psys->activate = true;
		break;
	}
	case 'P':
	{
		//pompas
		
			srand(time(NULL));
			//aceleraciones aleatorias 
			float rx = rand() % 2+0;
			float ry = rand() % 2+1;
			float rz = rand() % 2+0;

			//para poner aceleraciones positivas y negativas  
			float negx = rand() % 10+1;
			float negy = rand() % 10+1;
			float negz = rand() % 10+1;

			int tamrnd = rand() % 4 + 1;

			if (negx < 5) {
				rx=rx-(2*rx);
			}
			else if (negy < 5) {
				ry=ry-(2*ry);
			}
			else if (negz < 5) {
				rz=rz-(2*rz);
			}

			//bullets.push_back(new Mshot(0.1, {GetCamera()->getDir()*70 }, { GetCamera()->getEye() }, 0.7, { rx/10,ry/10,rz/10},{0,0,1,1},tamrnd));
		
		break;
	}

	case 'G':
		//if (!psys->getgrav) {
		if (!wmg->getgrav) {
			psys->getgrav = true;
			
		}
		if (!psys->getgrav) {
			//wmg->getgrav = true;
		}
		
		break;
	case 'T':
		/*if (!psys->getwind) { 
			psys->getwind = true;
			psys->createwindAreaForce();
		}*/

		if (!wmg->getwind) {
			
			wmg->getwind = true;
			
			wmg->createwindAreaForce();
		}
		
		break;
	
	case 'U':
		//if (!psys->getexplosion) {
		if (!wmg->getexplosion) {
			//psys->getexplosion = true;
			wmg->getexplosion = true;
			//psys->createExplosionForce();
			wmg->createExplosionForce();
		}
		
		break;
	
	case 'H':
		//if (!psys->getWhirl) {
		if (!wmg->getWhirl) {
			//psys->getWhirl = true;
			wmg->getWhirl = true;
			
		}
		
		break;
	case 'X':
		//desactivar
		if (psys->getgrav) {
			psys->getgrav = false;
	
		}
		if (wmg->getgrav) {
			
			wmg->getgrav = false;
		}
		if (psys->getwind) {
		    psys->getwind = false;
        }

		if (wmg->getwind) {
			
			wmg->getwind = false;
		}
		//if (psys->getexplosion) {
		if (wmg->getexplosion) {
			//psys->getexplosion = false;
			wmg->getexplosion = false;
		}
		//if (psys->getWhirl) {
		if (wmg->getWhirl) {
			//psys->getWhirl = false;
			wmg->getWhirl = false;
		}
		//psys->eraseForces();

		break;

	case 'K':
		if (psys != NULL) {
			if (!psys->create) {
				psys->create = true;
			}
		}
		break;

	case 'M':
		if (psys != NULL) {
			if (!psys->flotar) {
				psys->flotar = true;
			}
		}

	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{

	
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
	if (actor2->getName() == "media") {
		psys->activate = true;
		wmg->addPoints();
	}

	if (actor2->getName() == "media2") {
		wmg->addPoints();
		psys->activate = true;
	}

	if (actor2->getName() == "alta3") {
		wmg->addPoints();
		psys->activate = true;
	}

	if (actor2->getName() == "alta4") {
		wmg->addPoints();
		psys->activate = true;
	}

	if (actor2->getName() == "alta5") {
		wmg->addPoints();
		psys->activate = true;
	}
	
	//gScene->removeActor(*actor2, false);


}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}