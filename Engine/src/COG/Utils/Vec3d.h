#pragma once

#include "precomp/precomp.h"

#include "COG/Core.h"
#include "COG/Log.h"

#include "Vec2d.h"

class COG_API Vec3d {
	private: 
	double x, y, z;
	
	public:
	//Constructors
	
	//Set all to the same value	(defaults to 0)
	constexpr inline Vec3d(double all = 0) noexcept : x(all), y(all), z(all) {}
	//Specify each value
	constexpr inline Vec3d(double x_in, double y_in, double z_in) noexcept 
		: x(x_in), y(y_in), z(z_in) {}
	//Get values from an array
	constexpr inline Vec3d(const std::array<double, 3>& arr) noexcept 
		: x(arr[0]), y(arr[1]), z(arr[2]) {}
	//Get values from a tuple
	constexpr inline Vec3d(const std::tuple<double, double, double>& arr) noexcept 
		: x(std::get<0>(arr)), y(std::get<1>(arr)), z(std::get<2>(arr)){}

	//Const functions

	constexpr inline double x_val() const noexcept { return x; }
	constexpr inline double y_val() const noexcept { return y; }
	constexpr inline double z_val() const noexcept { return z; }

	constexpr inline Vec2d xy() const noexcept { return Vec2d(x, y); }
	constexpr inline Vec2d xz() const noexcept { return Vec2d(x, z); }
	constexpr inline Vec2d yz() const noexcept { return Vec2d(y, z); }

	constexpr operator std::array<double, 3>(){
		return {x, y, z};
	}
	
	constexpr inline double sqr_magnitude() const noexcept {
		return x*x + y*y + z*z;
	}

	constexpr inline double dot(const Vec3d& rhs) const noexcept {
		return x*rhs.x + y*rhs.y + z*rhs.z;
	}

	constexpr inline Vec3d cross(const Vec3d& rhs) const noexcept {
		return Vec3d(y*rhs.z - z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y - y*rhs.x);
	}

	//Operator overloads (const at top)

	inline double operator[](unsigned short index){
		 COG::COG_ASSERT_INTERNAL(index < 3, "A Vec3d was incorrectly accessed!");
		 switch(index) {
			 case 0: return x;
			 case 1: return y;
			 case 2: return z;
			 default:
				 COG::error_internal("A Vec3d was incorrectly accessed!");
				 throw std::invalid_argument("A Vec3d[] can only accept 0, 1, or 2!");
		 }
	}

	constexpr inline Vec3d operator+(const Vec3d& rhs) const noexcept {
		return Vec3d(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	constexpr inline Vec3d operator-(const Vec3d& rhs) const noexcept { 
		return Vec3d(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	constexpr inline Vec3d operator*(double rhs) const noexcept {
		return Vec3d(x * rhs, y * rhs, z * rhs);
	}
	
	constexpr inline Vec3d operator/(double rhs) const {
		return Vec3d(x / rhs, y / rhs, z / rhs);
	}

	constexpr inline void operator+=(const Vec3d& rhs) noexcept {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
	}

	constexpr inline void operator-=(const Vec3d& rhs) noexcept {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
	}

	constexpr inline void operator*=(double rhs) noexcept {
		x *= rhs;
		y *= rhs;
		z *= rhs;
	}

	constexpr inline void operator/=(double rhs) {
		x /= rhs;
		y /= rhs;
		z /= rhs;
	}
};

namespace std {

	inline std::string to_string(const Vec3d& val){
		std::stringstream stream("(");
		stream << val.x_val() << ", " << val.y_val() << ", " << val.z_val() << ")";
		return stream.str();
	}
}

inline std::ostream& operator<<(std::ostream& lhs, const Vec3d& rhs){
	lhs << std::to_string(rhs);
	return lhs;
}
