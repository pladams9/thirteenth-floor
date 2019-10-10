/*
 * VoxelDrawable.h
 *
 *  Created on: Oct 6, 2019
 *      Author: pladams9
 */

#ifndef COMPONENTS_VOXELDRAWABLE_H_
#define COMPONENTS_VOXELDRAWABLE_H_


/* INCLUDES */
#include <components/Voxel.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <tuple>

#include "Component.h"
#include "Utilities.h"


namespace TF
{
namespace Comp
{


class VoxelDrawable : public Component
{
private:
	std::unordered_map<VoxelType, std::vector<VoxelID>> _voxelIDs;
	std::unordered_map<VoxelType, Util::Drawable> _drawables;

public:
	std::string GetType() const { return "VoxelDrawable"; }
	VoxelDrawable(std::unordered_map<VoxelType, Util::Drawable> drawables)
	: _drawables(drawables) {}

	std::unordered_map<VoxelType, std::vector<VoxelID>> GetVoxelIDs() { return _voxelIDs; }
	std::unordered_map<VoxelType, Util::Drawable> GetDrawables() { return _drawables; }

	void SetVoxelIDs(std::unordered_map<VoxelType, std::vector<VoxelID>> voxelIDs) { _voxelIDs = voxelIDs; }
};


}
}


#endif /* COMPONENTS_VOXELDRAWABLE_H_ */