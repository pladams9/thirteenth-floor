/*
 * utilities.h
 *
 *  Created on: Sep 25, 2019
 *      Author: pladams9
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_


/* INCLUDES */
#include <sstream>


namespace TF
{
namespace Util
{


// Workaround for broken std::to_string in MinGW
template <typename T>
std::string to_string(T arg)
{
	std::stringstream ss;
	ss << arg;
	return ss.str();
}


}
}


#endif /* UTILITIES_H_ */
