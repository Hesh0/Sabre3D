#pragma once

#pragma region Vec2 class

struct Vec2
{
	float x, y;
private:
	char m_VecStrBuff[80];

public:
	Vec2(float&& xval, float&& yval);
	Vec2(float& xval, float& yval);
	
	~Vec2();

	inline Vec2 Add(const Vec2& other) const;
	inline Vec2 Subtract(const Vec2& other) const;
	inline float Mult(const Vec2& other);
	inline Vec2& Divide(float scalar); 
	inline void Scale(float scalar);

	inline float Length() const;
	inline float Distance(const Vec2& other) const;
	inline Vec2 Normalize() const;
	inline void NormalizeInPlace();

	inline const char* ToString();

	Vec2 operator+(const Vec2& other) const;
	Vec2& operator+=(const Vec2& other);
	Vec2& operator-=(const Vec2& other);

	friend Vec2 operator+(const Vec2& lhs, const Vec2& rhs);
	
	friend Vec2 operator-(const Vec2& lhs, const Vec2& rhs);
	friend float operator*(Vec2& lhs, const Vec2& rhs); // Dot Product.
	friend Vec2& operator*(Vec2& lhs, float rhs);
	friend Vec2& operator*(float lhs, Vec2& rhs);

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
private:
	char m_VecStrBuff[80];
public:
	Vec3(float&& xval, float&& yval, float&& zval);
	Vec3(float& xval, float& yval, float& zval);

	~Vec3();
	
	Vec3 Add(const Vec3& other) const;
	Vec3 Subtract(const Vec3& other) const;
	float Mult(const Vec3& other);
	Vec3& Divide(float scalar);
	void Scale(float scalar);
	Vec3 Cross(const Vec3& other) const;

	inline float Length() const;
	inline float Distance(const Vec3& other) const;

	inline Vec3 Normalize() const;
	inline void NormalizeInPlace();

	inline const char* ToString();

	Vec3& operator+=(const Vec3& other);
	Vec3& operator-=(const Vec3& other);

	friend Vec3 operator+(Vec3& lhs, const Vec3& rhs);
	friend Vec3 operator-(const Vec3& lhs, const Vec3& rhs);
	friend float operator*(Vec3& lhs, const Vec3& rhs); 
	friend Vec3& operator*(Vec3& lhs, float rhs);
	friend Vec3& operator*(float lhs, Vec3& rhs);
	friend Vec3& operator/(Vec3& lhs, const float& rhs);
	friend Vec3 operator%(Vec3& lhs, Vec3& rhs); // Cross product.
	friend bool operator==(const Vec3& lhs, const Vec3& rhs);
	friend bool operator!=(const Vec3& lhs, const Vec3& rhs);
	friend std::ostream& operator<<(std::ostream& out, const Vec3& vec);
	friend Vec3& operator*(float lhs, Vec3& rhs);
};

#pragma endregion

#pragma region Vec4 class

struct Vec4 
{
	float x, y, z, w;
	float vec4[4];

private:
	char m_VecStrBuff[80];

public:
	Vec4(float&& xval, float&& yval, float&& zval, float&& wval);
	Vec4(float&& xval, float&& yval, float&& zval);
	Vec4(float& xval, float& yval, float& zval, float& wval);
	Vec4(float& xval, float& yval, float& zval);
	
	~Vec4() {}

	inline const char* ToString();

	// Passing a poiter to an array of length 4 so for checking from the compiler that array is of the right length.
	Vec4& operator=(const float(*vec)[4]);
	Vec4& operator=(const Vec4& other);

	
	friend std::ostream& operator<<(std::ostream& out, const Vec4& vec);
};

#pragma endregion

#pragma region inline definitions

#pragma region Vec2 inlines

Vec2 Vec2::Add(const Vec2& other) const
{
	float xx = x + other.x;
	float yy = y + other.y;

	return Vec2(xx, yy);
}

Vec2 Vec2::Subtract(const Vec2& other) const
{
	float xx = x - other.x;
	float yy = y - other.y;

	return Vec2(xx, yy);
}

float Vec2::Mult(const Vec2& other)
{
	return x * other.y + y * other.y;
}

Vec2& Vec2::Divide(float scalar)
{
	x /= scalar;
	y /= scalar;

	return *this;
}

void Vec2::Scale(float scalar)
{
	x *= scalar;
	y *= scalar;
}

float Vec2::Length() const
{
	return sqrt(x*x + y*y);
}

float Vec2::Distance(const Vec2& other) const
{
	Vec2 diffVec = -1 * (*this - other);
	return sqrt(diffVec * diffVec);
}

Vec2 Vec2::Normalize() const
{
	float length = Length();

	float xx = x / length;
	float yy = y / length;

	return Vec2(xx, yy);
}

void Vec2::NormalizeInPlace()
{
	float length = Length();

	x = x / length;
	y = y / length;
}

const char* Vec2::ToString()
{
	sprintf_s(m_VecStrBuff, _arrlen(m_VecStrBuff), "[%f, %f]", x, y);

	return m_VecStrBuff;
}

#pragma endregion Vec2 inlines

#pragma region Vec3 inlines



float Vec3::Length() const
{
	return sqrt(x*x + y*y + z*z);
}

float Vec3::Distance(const Vec3& other) const
{
	Vec3 diffVec = -1 * (*this - other);
	return sqrt(diffVec * diffVec);
}

Vec3 Vec3::Normalize() const
{
	float length = Length();

	float xx = x / length;
	float yy = y / length;
	float zz = z / length;

	return Vec3(xx, yy, zz);
}

void Vec3::NormalizeInPlace()
{
	float length = Length();

	x = x / length;
	y = y / length;
	z = z / length;
}





const char* Vec3::ToString()
{
	sprintf_s(m_VecStrBuff, _arrlen(m_VecStrBuff), "[%f, %f, %f]", x, y, z);

	return m_VecStrBuff;
}

#pragma endregion Vec3 inlines

#pragma region Vec4 inlines
const char* Vec4::ToString()
{
	sprintf_s(m_VecStrBuff, _arrlen(m_VecStrBuff), "[%f, %f, %f, %f]", x, y, z, w);

	return m_VecStrBuff;
}

#pragma endregion Vec4 inlines



#pragma endregion