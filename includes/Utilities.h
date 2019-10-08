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
	vec2() {};
	vec2(T x, T y) : x(x), y(y) {};
	vec2(T val) : x(val), y(val) {};
};

template <typename T>
struct vec3
{
	union
	{
		struct {T x, y, z;};
		struct {T r, g, b;};
		struct {T yaw, pitch, roll;};
		T vals[3];
	};

	vec3() {};
	vec3(T x, T y, T z) : x(x), y(y), z(z) {};
	vec3(T val) : x(val), y(val), z(val) {};

	vec3& operator+=(const vec3& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
	friend vec3 operator+(vec3 lhs, const vec3& rhs) { return lhs.operator+=(rhs); }
	vec3& operator-=(const vec3& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
	friend vec3 operator-(vec3 lhs, const vec3& rhs) { return lhs.operator-=(rhs); }
	vec3& operator*=(const vec3& rhs) { x *= rhs.x; y *= rhs.y; z *= rhs.z; return *this; }
	friend vec3 operator*(vec3 lhs, const vec3& rhs) { return lhs.operator*=(rhs); }
	vec3& operator/=(const vec3& rhs) { x /= rhs.x; y /= rhs.y; z /= rhs.z; return *this; }
	friend vec3 operator/(vec3 lhs, const vec3& rhs) { return lhs.operator/=(rhs); }

	vec3& operator+=(const T& rhs) { x += rhs; y += rhs; z += rhs; return *this; }
	friend vec3 operator+(vec3 lhs, const T& rhs) { return lhs.operator+=(rhs); }
	vec3& operator-=(const T& rhs) { x -= rhs; y -= rhs; z -= rhs; return *this; }
	friend vec3 operator-(vec3 lhs, const T& rhs) { return lhs.operator-=(rhs); }
	vec3& operator*=(const T& rhs) { x *= rhs; y *= rhs; z *= rhs; return *this; }
	friend vec3 operator*(vec3 lhs, const T& rhs) { return lhs.operator*=(rhs); }
	vec3& operator/=(const T& rhs) { x /= rhs; y /= rhs; z /= rhs; return *this; }
	friend vec3 operator/(vec3 lhs, const T& rhs) { return lhs.operator/=(rhs); }
};
using vec3i = vec3<int>;
using vec3f = vec3<float>;
using vec3d = vec3<double>;

template <typename T>
struct vec4
{
  union
  {
    struct {T x, y, z, w;};
    struct {T r, g, b, a;};
    T vals[4];
  };
  vec4() {};
  vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {};
  vec4(T val) : x(val), y(val), z(val), w(val) {};
};

// Material struct
struct Material
{
	vec4<float> ambient = vec4<float>(0.1f, 0.1f, 0.1f, 0.1f);
	vec4<float> diffuse = vec4<float>(1.0f, 1.0f, 1.0f, 1.0f);
	vec4<float> specular = vec4<float>(1.0f, 1.0f, 1.0f, 1.0f);
	float specular_power = 0.5f;
};


struct Drawable
{
	std::string modelNamde = "";
	std::string shaderName = "";
	Material material;
};


}
}


#endif /* UTILITIES_H_ */
