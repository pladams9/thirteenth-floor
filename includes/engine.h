/*
 * engine.h
 *
 *  Created on: Sep 10, 2019
 *      Author: pladams9
 */

#ifndef INCLUDES_ENGINE_H_
#define INCLUDES_ENGINE_H_


/* INCLUDES */
#include <unordered_map>
#include <string>
#include <vector>

namespace TF
{


/* FORWARD DECLARATIONS */
class Graphics;
class Component;


/* TYPEDEFS */
using EntityID = unsigned int;

using ComponentMap = std::unordered_map<EntityID, Component*>;


/* CLASS DEFINITIONS */
class Engine
{
private:
	Graphics* graphics; // TODO: Replace with systems object?
	EntityID nextEntityID = 0;
	std::unordered_map<std::string, ComponentMap> components;

public:
	Engine(Graphics* g);

	void MainLoop();
	void AddEntity(std::vector<Component*> comps);
	void AddComponent(Component* comp, EntityID entityID);

	std::vector<std::vector<Component*>> GetComponents(std::vector<std::string> comp_types);
};


}


#endif /* INCLUDES_ENGINE_H_ */
