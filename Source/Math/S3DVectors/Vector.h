#pragma once

#pragma region Vec2 class

struct Vec2
{
	float x, y;

	Vec2(float&& xval, float&& yval);
	Vec2(float& xval, float& yval);
	Vec2(int&& xval, int&& yval);
	Vec2(int& xval, int& yval);

	~Vec2();

	Vec2& Add(const Vec2& other);
	Vec2& Subtract(const Vec2& other);
	float Mult(const Vec2& other);
	Vec2& Divide(float scalar); 
	void Scale(float scalar);

	float Length();
	Vec2 Normalize();
	void NormalizeInPlace();

	Vec2& operator+=(const Vec2& other);
	Vec2& operator-=(const Vec2& other);

	friend Vec2& operator+(Vec2& lhs, const Vec2& rhs);
	friend Vec2& operator-(Vec2& lhs, const Vec2& rhs);
	friend float operator*(Vec2& lhs, const Vec2& rhs);
	friend Vec2& operator/(Vec2& lhs, const float& rhs);
	friend bool operator==(const Vec2& lhs, const Vec2 rhs);
	friend bool operator!=(const Vec2& lhs, const Vec2 rhs);
	friend std::ostream& operator<<(std::ostream& out, const Vec2& vec);
};

#pragma endregion

#pragma region Vec3 class
struct Vec3 
{
	float x, y, z;

	Vec3(float&& xval, float&& yval, float&& zval);
	Vec3(float& xval, float& yval, float& zval);
	Vec3(int&& xval, int&& yval, int&& zval); 
	Vec3(int& xval, int& yval, int& zval);

	~Vec3();
	
	Vec3& Add(const Vec3& other);
	Vec3& Subtract(const Vec3& other);
	float Mult(const Vec3& other);
	Vec3& Divide(float scalar);
	void Scale(float scalar);
	Vec3 Cross(const Vec3& other);

	float Length();
	Vec3 Normalize();
	void NormalizeInPlace();

	Vec3& operator+=(const Vec3& other);
	Vec3& operator-=(const Vec3& other);

	friend Vec3& operator+(Vec3& lhs, const Vec3& rhs);
	friend Vec3& operator-(Vec3& lhs, const Vec3& rhs);
	friend float operator*(Vec3& lhs, const Vec3& rhs);
	friend Vec3& operator/(Vec3& lhs, const float& rhs);
	friend bool operator==(const Vec3& lhs, const Vec3 rhs);
	friend bool operator!=(const Vec3& lhs, const Vec3 rhs);
	friend std::ostream& operator<<(std::ostream& out, const Vec3& vec);
};

#pragma region Vec4 class
struct Vec4 
{
	float x, y, z, w;

	Vec4(float&& xval, float&& yval, float&& zval, float&& wval);
	Vec4(float& xval, float& yval, float& zval, float& wval);
	Vec4(int&& xval, int&& yval, int&& zval, int&& wval);
	Vec4(int& xval, int& yval, int& zval, int& wval);

	~Vec4() {}
	
	friend std::ostream& operator<<(std::ostream& out, const Vec4& vec);
};

#pragma end region
