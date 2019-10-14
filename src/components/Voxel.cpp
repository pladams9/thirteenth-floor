/**
 * Voxel.h
 *
 */

#include "components/Voxel.h"

bool operator==(const TF::Voxel& lhs, const TF::Voxel& rhs)
{
    return lhs.ID == rhs.ID;
}
