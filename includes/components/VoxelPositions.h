/**
 * VoxelPositions.h
 *
 */

#ifndef COMPONENTS_VOXELPOSITIONS_H_
#define COMPONENTS_VOXELPOSITIONS_H_

/* INCLUDES */
#include <string>

#include "engine/Component.h"

namespace TF
{
namespace Comp
{


class VoxelPositions : public Component
{
public:
	std::string GetType() const { return "VoxelPositions"; }
	VoxelPositions();

private:

};


}
}

#endif /* COMPONENTS_VOXELPOSITIONS_H_ */
