/*
 * engine.h
 *
 *  Created on: Sep 10, 2019
 *      Author: pladams9
 */

#ifndef INCLUDES_ENGINE_H_
#define INCLUDES_ENGINE_H_


namespace TF
{


/* FORWARD DECLARATIONS */
class Graphics;


/* CLASS DEFINITIONS */
class Engine
{
private:
	Graphics* graphics;
public:
	Engine(Graphics* g);

	void mainLoop();
};


}


#endif /* INCLUDES_ENGINE_H_ */
