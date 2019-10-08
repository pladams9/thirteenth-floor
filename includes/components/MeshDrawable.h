/*
 * Drawable.h
 *
 *  Created on: Oct 6, 2019
 *      Author: pladams9
 */

#ifndef COMPONENTS_MESHDRAWABLE_H_
#define COMPONENTS_MESHDRAWABLE_H_


/* INCLUDES */
#include <string>

#include "Component.h"
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

	std::string GetDrawable() { return _drawable; }
};


}
}


#endif /* COMPONENTS_MESHDRAWABLE_H_ */
