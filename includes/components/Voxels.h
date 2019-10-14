/**
 * Voxels.h
 *
 */

#ifndef COMPONENTS_VOXELS_H_
#define COMPONENTS_VOXELS_H_

/* INCLUDES */
#include <unordered_map>
#include <string>
#include <vector>

#include "components/Voxel.h"
#include "engine/Component.h"
#include "Utilities.h"

namespace TF
{
namespace Comp
{


class Voxels : public Component
{
public:
	std::string GetType() const { return "Voxels"; }

	VoxelID AddVoxel(VoxelType type, Util::vec3d position)
	{
		Voxel v;
		v.ID = _nextVoxelID++;
		v.type = type;
		v.position = position;

		_voxels[v.ID] = v;
		_voxelsByType[v.type].push_back(v);

		_hasBeenUpdated = true;

		return v.ID;
	}

	void RemoveVoxel(VoxelID id)
	{
		// Find the voxel
		auto it = _voxels.find(id);
		if(it == _voxels.end()) return;
		Voxel v = (*it).second;

		// Remove from main list
		_voxels.erase(it);

		// Remove from type list
		auto v_list = _voxelsByType.at(v.type);
		for(auto it = v_list.begin(); it != v_list.end(); ++it)
		{
			if(*it == v) v_list.erase(it);
		}

		_hasBeenUpdated = true;
	}

	std::vector<Voxel> GetVoxels(VoxelType type)
	{
		return _voxelsByType[type];
	}

	bool HasBeenUpdated()
	{
		return _hasBeenUpdated;
	}

	void ClearUpdateFlag()
	{
		_hasBeenUpdated = false;
	}

private:
	VoxelID _nextVoxelID = 1;
	std::unordered_map<VoxelID, Voxel> _voxels;
	std::unordered_map<VoxelType, std::vector<Voxel>> _voxelsByType;
	bool _hasBeenUpdated = true;
};


}
}

#endif /* COMPONENTS_VOXELS_H_ */
