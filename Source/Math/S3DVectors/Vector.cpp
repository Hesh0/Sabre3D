#include "../../Sabre3D/Sabre3Dstd.h"
#include "Vector.h"



#pragma region Vec2 definition

Vec2::Vec2(float&& xval, float&& yval) : x{xval}, y{yval} {}
Vec2::Vec2(float& xval, float& yval) : x{xval}, y{yval} {}

Vec2::~Vec2() {}


Vec2 Vec2::operator+(const Vec2& other) const
{
	return Add(other);
}

Vec2& Vec2::operator+=(const Vec2& other)
{
	x += other.x;
	y += other.y;

	return *this;
}

Vec2& Vec2::operator-=(const Vec2& other)
{
	x -= other.x;
	y -= other.y;

	return *this;
}

#pragma region Vec2 friend operator overload definitons

Vec2 operator+(Vec2& lhs, const Vec2& rhs)
{
	return lhs.Add(rhs);
}

Vec2 operator-(const Vec2& lhs, const Vec2& rhs) 
{
	return lhs.Subtract(rhs);
}

float operator*(Vec2& lhs, const Vec2& rhs)
{
	return lhs.Mult(rhs);
}

Vec2& operator*(Vec2& lhs, float rhs)
{
	lhs.x *= rhs;
	lhs.y *= rhs;

	return lhs;
}

Vec2& operator*(float lhs, Vec2& rhs)
{
	rhs.x *= lhs;
	rhs.y *= lhs;

	return rhs;
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
	return out << '[' << precision(2) << vec.x << ", " << vec.y << ']';
}

#pragma endregion Vec2 friend operator overload definitons

#pragma endregion Vec2 definition

#pragma region Vec3 definition

Vec3::Vec3(float&& xval, float&& yval, float&& zval) : x{xval}, y{yval}, z{zval} {}
Vec3::Vec3(float& xval, float& yval, float& zval) : x{xval}, y{yval}, z{zval} {}

Vec3::~Vec3(){}

Vec3 Vec3::Add(const Vec3& other) const
{
	float xx = x + other.x;
	float yy = y + other.y;
	float zz = z + other.z;

	return Vec3(xx, yy, zz);
}
Vec3 Vec3::Subtract(const Vec3& other) const
{
	float xx = x - other.x;
	float yy = y - other.y;
	float zz = z - other.z;

	return Vec3(xx, yy, zz);
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

Vec3 Vec3::Cross(const Vec3& other) const
{
	return Vec3(y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x);
}

void Vec3::Scale(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
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

Vec3 operator+(const Vec3& lhs, const Vec3& rhs)
{
	return lhs.Add(rhs);
}

Vec3 operator-(const Vec3& lhs, const Vec3& rhs)
{
	return lhs.Subtract(rhs);
}

float operator*(Vec3& lhs, const Vec3& rhs)
{
	return lhs.Mult(rhs);
}

Vec3& operator*(Vec3& lhs, float rhs)
{
	lhs.x *= rhs;
	lhs.y *= rhs; 
	lhs.z *= rhs;

	return lhs;
}

Vec3& operator*(float lhs, Vec3& rhs)
{
	rhs.x *= lhs;
	rhs.y *= lhs;
	rhs.z *= lhs;

	return rhs;
}

Vec3 operator%(Vec3& lhs, Vec3& rhs)
{
	return lhs.Cross(rhs); 
}

Vec3& operator/(Vec3& lhs, const float& rhs)
{
	return lhs.Divide(rhs);
}

bool operator==(const Vec3& lhs, const Vec3& rhs)
{

	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

bool operator!=(const Vec3& lhs, const Vec3& rhs)
{
	return lhs.x != rhs.x && lhs.y != rhs.y && lhs.z != rhs.z;
}

std::ostream& operator<<(std::ostream& out, const Vec3& vec)
{
	return out << '[' << precision(2) << vec.x << ", " << vec.y << ", " << vec.z << ']';
}

#pragma endregion Vec3 friend operator overload definitons

#pragma endregion Vec3 definition

#pragma region Vec4 definition

Vec4::Vec4(float&& xval, float&& yval, float&& zval, float&& wval) : x{xval}, y{yval}, z{zval}, w{wval} //vec4{DBG_NEW float[4]}
{
	vec4[0] = x;
	vec4[1] = y;
	vec4[2] = z;
	vec4[3] = w;
}

Vec4::Vec4(float&& xval, float&& yval, float&& zval) : x{ xval }, y{ yval }, z{ zval }, w{1.0f}
{
	vec4[0] = x;
	vec4[1] = y;
	vec4[2] = z;
	vec4[3] = 1;
}

Vec4::Vec4(float& xval, float& yval, float& zval, float& wval) : x{xval}, y{yval}, z{zval}, w {wval} 
{
	vec4[0] = xval;
	vec4[1] = y;
	vec4[2] = z;
	vec4[3] = w;
}

Vec4::Vec4(float& xval, float& yval, float& zval) : x{xval}, y{yval}, z{zval}, w{1.0f} 
{
	vec4[0] = xval;
	vec4[1] = y;
	vec4[2] = z;
	vec4[3] = w;
}

Vec4& Vec4::operator=(const float (*vec)[4])
{
	vec4[0] = (*vec)[0]; // De-reference first to get access to the array.
	x = (*vec)[0];
	vec4[1] = (*vec)[1];
	y = (*vec)[1];
	vec4[2] = (*vec)[2];
	z=  (*vec)[2];
	vec4[3] = (*vec)[3];
	w = (*vec)[3];
	
	return *this;
}

Vec4& Vec4::operator=(const Vec4& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;

	for (int i = 0; i < 4; i++)
	{
		vec4[i] = other.vec4[i];
	}

	return *this;
}

#pragma region friend operator definition

std::ostream& operator<<(std::ostream& out, const Vec4& vec)
{
	return out << '[' << precision(6) << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w <<']';
}

#pragma endregion

#pragma endregion Vec4 definition