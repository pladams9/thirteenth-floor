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
#include <engine/Component.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <tuple>

#include "Utilities.h"


namespace TF
{
namespace Comp
{


class VoxelDrawable : public Component
{
public:
	std::string GetType() const { return "VoxelDrawable"; }
	VoxelDrawable(std::unordered_map<VoxelType, Util::Drawable> drawables, double voxelScale = 1.0)
	: _drawables(drawables), _voxelScale(voxelScale) {}

	std::unordered_map<VoxelType, Util::Drawable> GetDrawables() { return _drawables; }
	double GetVoxelScale() { return _voxelScale; }
private:
	std::unordered_map<VoxelType, Util::Drawable> _drawables;
	double _voxelScale;
};


}
}


#endif /* COMPONENTS_VOXELDRAWABLE_H_ */
