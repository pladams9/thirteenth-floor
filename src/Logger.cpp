/*
 * Logger.cpp
 *
 *  Created on: Oct 5, 2019
 *      Author: pladams9
 */

#include "Logger.h"


/* INCLUDES */
#include <chrono>
#include <ctime>
#include <sstream>
#include <iostream>


namespace TF
{


/* FREE FUNCTIONS */
Logger& LOGGER()
{
	static Logger instance;
	return instance;
}


struct tm* GetDateTime()
{
	std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	return localtime(&t);
}

std::string GetDateTimeFileNameString()
{
	struct tm* datetime = GetDateTime();

	std::stringstream dt_string;
	dt_string << (datetime->tm_year + 1900) << "-" << (datetime->tm_mon + 1) << "-" << datetime->tm_mday << "_"
				<< datetime->tm_hour << "-" <<  datetime->tm_min;

	char second_letter = (char)(((datetime->tm_sec * 26)/ 60) + 97);
	dt_string << "_" << second_letter;

	return dt_string.str();
}

std::string GetDateTimeString()
{
	struct tm* datetime = GetDateTime();

	std::stringstream dt_string;
	dt_string << (datetime->tm_year + 1900) << "-" << (datetime->tm_mon + 1) << "-" << datetime->tm_mday << " "
				<< datetime->tm_hour << ":" <<  datetime->tm_min << ":" << datetime->tm_sec;

	return dt_string.str();
}


/* METHOD DEFINITIONS */
Logger::Logger()
{
	std::stringstream log_file_name;
	log_file_name << "../logs/" << GetDateTimeFileNameString() << ".log";
	this->logFile.open(log_file_name.str(), std::ofstream::out);
}

Logger::~Logger()
{
	this->logFile.close();
}

void Logger::Log(LogLevel level, std::string message, bool screen_only)
{
	if(level > this->fileThreshold && level > this->screenThreshold) return;

	std::stringstream output;

	output << GetDateTimeString() << " ";

	switch(level)
	{
	case ERROR:
		output << "[ERROR] ";
		break;
	case INFO:
		output << "[INFO] ";
		break;
	case DEBUG:
		output << "[DEBUG] ";
		break;
	default:
		output << "[LOG] ";
		break;
	}

	output << message << "\n";

	if((level <= this->fileThreshold) && (!screen_only))
	{
		this->logFile << output.str();
		this->logFile.flush();
		_readyForFileBreak = true;
	}
	if(level <= this->screenThreshold)
	{
		std::cout << output.str();
		std::cout.flush();
		_readyForScreenBreak = true;
	}

}

void Logger::LogBreakLine()
{
	if(_readyForFileBreak)
	{
		this->logFile << "\n";
		this->logFile.flush();
		_readyForFileBreak = false;
	}
	if(_readyForScreenBreak)
	{
		std::cout << "\n";
		std::cout.flush();
		_readyForScreenBreak = false;
	}
}

void Logger::SetLogThreshold(LogLevel file, LogLevel screen)
{
	this->fileThreshold = file;
	this->screenThreshold = screen;
}


}
