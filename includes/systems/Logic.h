/*
 * logic.h
 *
 *  Created on: Sep 21, 2019
 *      Author: pladams9
 */

#ifndef SYSTEMS_LOGIC_H_
#define SYSTEMS_LOGIC_H_


/* INCLUDES */
#include <System.h>
#include <chrono>
using namespace std::chrono;


namespace TF
{
namespace Sys
{


class LogicSystem : public System
{
private:
	steady_clock::time_point lastStep;
	duration<double, std::milli> timeStep;
	duration<double, std::milli> leftoverTime;

public:
	LogicSystem(Engine* engine);

	void Step();
};


}
}


#endif /* SYSTEMS_LOGIC_H_ */
