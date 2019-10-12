/**
 * MeshDrawable.h
 *
 * Indicates that an entity can be drawn as a single mesh, and gives access to
 * the appropriate mesh/shader/material info.
 *
 */

#ifndef COMPONENTS_MESHDRAWABLE_H_
#define COMPONENTS_MESHDRAWABLE_H_


/* INCLUDES */
#include <string>

#include "engine/Component.h"

#include "Utilities.h"


namespace TF
{
namespace Comp
{


class MeshDrawable : public Component
{
private:
	Util::Drawable _drawable;

public:
	std::string GetType() const { return "MeshDrawable"; }
	MeshDrawable(Util::Drawable drawable)
	: _drawable(drawable) {}

	Util::Drawable GetDrawable() { return _drawable; }
};


}
}


#endif /* COMPONENTS_MESHDRAWABLE_H_ */
