/*
 * EventLogger.h
 *
 *  Created on: Sep 24, 2019
 *      Author: pladams9
 */

#ifndef SYSTEMS_EVENTLOGGER_H_
#define SYSTEMS_EVENTLOGGER_H_


#include <systems/system.h>


namespace TF
{


/* CLASS DECLARATION */
class EventLoggerSystem : public System
{
public:
	EventLoggerSystem(Engine* eng);

	void Step();
};


}


#endif /* SYSTEMS_EVENTLOGGER_H_ */
