#include "../../Sabre3D/Sabre3Dstd.h"
#include <iomanip>
#include <math.h>

#include "Vector.h"

#define precision2 std::fixed << std::setprecision(2)

#pragma region Vec2 definition

Vec2::Vec2(float&& xval, float&& yval) : x{xval}, y{yval} {}
Vec2::Vec2(float& xval, float& yval) : x{xval}, y{yval} {}

Vec2::Vec2(int && xval, int && yval) : x{ (float)xval }, y{(float)yval} {}
Vec2::Vec2(int& xval, int& yval) : x{(float)xval}, y{(float)yval} {}

Vec2::~Vec2()
{
}

Vec2& Vec2::Add(const Vec2& other)
{
	this->x += other.x;
	this->y += other.y;

	return *this;
}

Vec2& Vec2::Subtract(const Vec2& other)
{
	this->x -= other.x;
	this->y -= other.y;

	return *this;
}

float Vec2::Mult(const Vec2& other)
{
	return this->x * other.y + this->y * other.y;
}

Vec2& Vec2::Divide(float scalar)
{
	this->x /= scalar;
	this->y /= scalar;

	return *this;
}

void Vec2::Scale(float scalar)
{
	x *= scalar;
	y *= scalar;
}

float Vec2::Length()
{
	return sqrt(x*x + y*y);
}

Vec2 Vec2::Normalize()
{
	float length = Length();

	x =  x / length;
	y =  y / length;

	return Vec2(x, y);
}

void Vec2::NormalizeInPlace()
{
	float length = Length();
	
	x = x / length;
	y = y / length;
}

Vec2& Vec2::operator+=(const Vec2& other)
{
	this->x += other.x;
	this->y += other.y;

	return *this;
}

Vec2& Vec2::operator-=(const Vec2& other)
{
	this->x -= other.x;
	this->y -= other.y;

	return *this;
}

#pragma region Vec2 friend operator overload definitons

Vec2& operator+(Vec2& lhs, const Vec2& rhs)
{
	return lhs.Add(rhs);
}

Vec2& operator-(Vec2& lhs, const Vec2& rhs)
{
	return lhs.Subtract(rhs);
}

float operator*(Vec2& lhs, const Vec2& rhs)
{
	return lhs.Mult(rhs);
}

Vec2& operator/(Vec2& lhs, const float& rhs)
{
	return lhs.Divide(rhs);
}

bool operator==(const Vec2& lhs, const Vec2 rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator!=(const Vec2& lhs, const Vec2 rhs)
{
	return lhs.x != rhs.x && lhs.y != rhs.y;
}

std::ostream& operator<<(std::ostream& out, const Vec2& vec)
{
	return out << '<' << precision2 << vec.x << ", " << precision2 << vec.y << '>';
}

#pragma endregion Vec2 friend operator overload definitons

#pragma endregion Vec2 definition

#pragma region Vec3 definition

Vec3::Vec3(float&& xval, float&& yval, float&& zval) : x{xval}, y{yval}, z{zval} {}
Vec3::Vec3(float& xval, float& yval, float& zval) : x{xval}, y{yval}, z{zval} {}

Vec3::Vec3(int&& xval, int&& yval, int&& zval) : x{(float)xval}, y{(float)yval}, z{(float)zval} {}
Vec3::Vec3(int& xval, int& yval, int& zval) : x{ (float)xval }, y{ (float)yval }, z{ (float)zval } {}

Vec3::~Vec3(){}

Vec3& Vec3::Add(const Vec3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}
Vec3& Vec3::Subtract(const Vec3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

float Vec3::Mult(const Vec3& other)
{
	return x * other.x + y * other.y + z * other.z;
}

Vec3& Vec3::Divide(float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;

	return *this;
}

Vec3 Vec3::Cross(const Vec3& other)
{
	return Vec3(y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x);
}

void Vec3::Scale(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
}

float Vec3::Length()
{
	return sqrt(x*x + y*y + z*z);
}

Vec3 Vec3::Normalize()
{
	float length = Length();

	x = x / length;
	y = y / length;
	z = z / length;

	return Vec3(x, y, z);
}

void Vec3::NormalizeInPlace()
{
	float length = Length();

	x = x / length;
	y = y / length;
	z = z / length;
}

Vec3& Vec3::operator+=(const Vec3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}

Vec3& Vec3::operator-=(const Vec3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

#pragma region Vec3 friend operator overload definitons

Vec3& operator+(Vec3& lhs, const Vec3& rhs)
{
	return lhs.Add(rhs);
}

Vec3& operator-(Vec3& lhs, const Vec3& rhs)
{
	return lhs.Subtract(rhs);
}

float operator*(Vec3& lhs, const Vec3& rhs)
{
	return lhs.Mult(rhs);
}

Vec3& operator/(Vec3& lhs, const float& rhs)
{
	return lhs.Divide(rhs);
}

bool operator==(const Vec3& lhs, const Vec3& rhs)
{

	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

bool operator!=(const Vec3& lhs, const Vec3 rhs)
{
	return lhs.x != rhs.x && lhs.y != rhs.y && lhs.z != rhs.z;
}

std::ostream& operator<<(std::ostream& out, const Vec3& vec)
{
	return out << '<' << precision2 << vec.x << ", " << precision2 << vec.y << ", " << precision2 << vec.z << '>';
}

#pragma endregion Vec3 friend operator overload definitons

#pragma endregion Vec3 definition

#pragma region Vec4 definition

Vec4::Vec4(float&& xval, float&& yval, float&& zval, float&& wval) : x{xval}, y{yval}, z{zval}, w {wval} {}
Vec4::Vec4(float& xval, float& yval, float& zval, float& wval) : x{xval}, y{yval}, z{zval}, w {wval} {}
Vec4::Vec4(int&& xval, int&& yval, int&& zval, int&& wval) : x{(float)xval}, y{(float)yval}, z{(float)zval}, w{(float)wval} {}
Vec4::Vec4(int& xval, int& yval, int& zval, int& wval) : x{(float)xval}, y{(float)yval}, z{(float)zval}, w{(float)wval} {}

#pragma region friend operator definition

std::ostream& operator<<(std::ostream& out, const Vec4& vec)
{
	return out << '<' << precision2 << vec.x << ", " << precision2 << vec.y << ", " << precision2 << vec.z << ", " << precision2 << vec.w <<'>';
}

#pragma endregion

#pragma endregion Vec4 definition

