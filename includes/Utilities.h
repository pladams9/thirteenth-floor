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

// Vector structs
template <typename T>
struct vec2
{
	T x, y;
	vec2(T x, T y) : x(x), y(y) {};
};

template <typename T>
struct vec3
{
  union
  {
    struct {T x, y, z;};
    struct {T r, g, b;};
    T vals[3];
  };
  vec3(T x, T y, T z) : x(x), y(y), z(z) {};
};


}
}


#endif /* UTILITIES_H_ */
