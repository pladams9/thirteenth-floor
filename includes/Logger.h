/*
 * Logger.h
 *
 *  Created on: Oct 5, 2019
 *      Author: pladams9
 */

#ifndef LOGGER_H_
#define LOGGER_H_


/* INCLUDE */
#include <string>
#include <fstream>

namespace TF
{


enum LogLevel
{
	NONE,
	ERROR,
	INFO,
	DEBUG
};


/* CLASS DECLARATIONS */
class Logger
{
public:
	Logger();
	~Logger();

	void Log(LogLevel level, std::string message);
	void SetLogThreshold(LogLevel file, LogLevel screen);

private:
	std::ofstream logFile;
	LogLevel fileThreshold=ERROR;
	LogLevel screenThreshold=INFO;
};


/* FREE FUNCTIONS */
Logger& LOGGER();


}


#endif /* LOGGER_H_ */
