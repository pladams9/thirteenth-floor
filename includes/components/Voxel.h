/*
 * Voxel.h
 *
 *  Created on: Oct 6, 2019
 *      Author: pladams9
 */

#ifndef COMPONENTS_VOXEL_H_
#define COMPONENTS_VOXEL_H_


/* INCLUDES */
#include "Vec.h"


namespace TF
{


using VoxelID = unsigned int;
using VoxelType = unsigned int;


struct Voxel
{
	VoxelID ID = 0;
	VoxelType type = 0;
	Util::vec3d position = Util::vec3d(0.0, 0.0, 0.0);
};


}
bool operator==(const TF::Voxel& lhs, const TF::Voxel& rhs);


#endif /* COMPONENTS_VOXEL_H_ */
