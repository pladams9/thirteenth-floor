/*
 * EventLogger.h
 *
 *  Created on: Sep 24, 2019
 *      Author: pladams9
 */

#ifndef SYSTEMS_EVENTLOGGER_H_
#define SYSTEMS_EVENTLOGGER_H_


#include <engine/System.h>


namespace TF
{
namespace Sys
{


/* CLASS DECLARATION */
class EventLogger : public System
{
public:
	EventLogger(Engine* eng);

	void Step();
};


}
}


#endif /* SYSTEMS_EVENTLOGGER_H_ */
