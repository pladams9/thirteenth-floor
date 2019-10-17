/*
 * factory.h
 *
 *  Created on: Sep 20, 2019
 *      Author: pladams9
 */

#ifndef ENTITYBUILDERS_H_
#define ENTITYBUILDERS_H_


/* INCLUDES */
#include <functional>
#include <vector>

#include "Vec.h"


namespace TF
{


/* FORWARD DECLARATIONS */
class Component;

namespace Comp
{
class Voxels;
struct Light;
}


/* FACTORY */
namespace Create
{


std::vector<Component*> Camera();
std::vector<Component*> Cube();
std::vector<Component*> RandomCube();
std::vector<Component*> VoxelChunk(std::function<void(Comp::Voxels*)> generator = nullptr);
std::vector<Component*> Light(Comp::Light l);


}

namespace VoxGen
{


void Ring(Comp::Voxels* voxels);
void Block(Comp::Voxels* voxels);


}


}


#endif /* ENTITYBUILDERS_H_ */
