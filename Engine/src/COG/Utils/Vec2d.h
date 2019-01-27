#pragma once

#include "precomp/precomp.h"

#include "COG/Core.h"
#include "COG/Log.h"

class COG_API Vec2d {
	private:
	double x, y;

	public:
	//Constructors

	//Set all to the same value
	constexpr inline Vec2d(double all = 0) noexcept : x(all), y(all) {}
	//Specify each value
	constexpr inline Vec2d(double x_in, double y_in) noexcept
		: x(x_in), y(y_in) {}
	//Get values from an array
	constexpr inline Vec2d(const std::array<double, 2>& arr) noexcept
		: x(arr[0]), y(arr[1]) {}
	//Get values from a pair
	constexpr inline Vec2d(const std::pair<double, double>& data) noexcept 
		: x(data.first), y(data.second) {}

	//Const functions

	constexpr inline double x_val() const noexcept { return x; }
	constexpr inline double y_val() const noexcept { return y; }

	constexpr operator std::array<double, 2>() {
		return {x, y};
	}

	constexpr operator std::pair<double, double>() {
		return {x, y};
	}

	constexpr inline double sqr_magnitude() const noexcept {
		return x * x + y * y;
	}

	constexpr inline double dot(const Vec2d& rhs) const noexcept {
		return x * rhs.x + y * rhs.y;
	}

	//Operator overloads (const at top)

	inline double operator[](unsigned short index) {
		COG::COG_ASSERT_INTERNAL(index < 2, "A Vec2d was incorrectly accessed!");
		switch(index) {
			case 0: return x;
			case 1: return y;
			default:
				COG::error_internal("A Vec2d was incorrectly accessed!");
				throw std::invalid_argument("A Vec2d[] can only accept 0 or 1!");
		}
	}

	constexpr inline Vec2d operator+(const Vec2d& rhs) const noexcept {
		return Vec2d(x + rhs.x, y + rhs.y);
	}

	constexpr inline Vec2d operator-(const Vec2d& rhs) const noexcept {
		return Vec2d(x - rhs.x, y - rhs.y);
	}

	constexpr inline Vec2d operator*(double rhs) const noexcept {
		return Vec2d(x * rhs, y * rhs);
	}

	constexpr inline Vec2d operator/(double rhs) const {
		return Vec2d(x / rhs, y / rhs);
	}

	constexpr inline void operator+=(const Vec2d& rhs) noexcept {
		x += rhs.x;
		y += rhs.y;
	}

	constexpr inline void operator-=(const Vec2d& rhs) noexcept {
		x -= rhs.x;
		y -= rhs.y;
	}

	constexpr inline void operator*=(double rhs) noexcept {
		x *= rhs;
		y *= rhs;
	}

	constexpr inline void operator/=(double rhs) {
		x /= rhs;
		y /= rhs;
	}
};

namespace std {

	inline std::string to_string(const Vec2d& val) {
		std::stringstream stream("(");
		stream << val.x_val() << ", " << val.y_val() << ")";
		return stream.str();
	}
}

inline std::ostream& operator<<(std::ostream& lhs, const Vec2d& rhs) {
	lhs << std::to_string(rhs);
	return lhs;
}

