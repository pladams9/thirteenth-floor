/**
 * Vec.h
 *
 */

#ifndef VEC_H_
#define VEC_H_


namespace TF
{
namespace Util
{


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


}
}


#endif /* VEC_H_ */
