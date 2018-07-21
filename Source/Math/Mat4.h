#pragma once

#include "SabreMath.h"
#include "S3DVectors\Vector.h"

class Mat4;

#pragma region S3DMath namespace declarations

namespace S3DMath {
	
	Mat4 ZeroMatrix();
	Mat4 IdentityMatrix();
	void IdentityMatrix(Mat4& mat);
	Mat4 ArbitraryMatrix(float (*mat4) [4*4]);
	
	Mat4 TranslationMatrix(float&& x, float&& y, float&& z);
	Mat4 TranslationMatrix(float& x, float& y, float& z);
	void TranslationMatrix(Mat4& mat, float&& x, float&& y, float&& z);
	void TranslationMatrix(Mat4& mat, float& x, float& y, float& z);
	
	Mat4 ScalingMatrix(float&& x, float&& y, float&& z);
	Mat4 ScalingMatrix(float& x, float& y, float& z);
	void ScalingMatrix(Mat4& mat, float&& x, float&& y, float&& z);
	void ScalingMatrix(Mat4& mat, float& x, float& y, float& z);
	Mat4 ArbitraryScaleMatrix(const Vec3& direction, float&& scaleFactor);
	Mat4 ArbitraryScaleMatrix(const Vec3& direction, float& scaleFactor);

	Mat4 ArbitraryRotation(Vec3& axis, float&& theta);
	Mat4 ArbitraryRotation(Vec3& axis, float& theta);
	
	Mat4 RotateXAxis(float& theta);
	Mat4 RotateXAxis(float&& theta);
	Mat4 RotateYAxis(float& theta);
	Mat4 RotateYAxis(float&& theta);
	Mat4 RotateZAxis(float& theta);
	Mat4 RotateZAxis(float&& theta);

	Mat4 OrthoProjectionMat(Vec3& direction);
}

#pragma endregion

class Mat4
{
public:
	typedef unsigned char Matflag;

private:
	float* m_Matrix;
	Mat4(float&& val);
	Mat4(float& val); 
	Mat4();
	Mat4(float (*mat)[4*4]);
	Mat4(Matflag flag, float&& x, float&& y, float&& z);
	Mat4(Matflag flag, float& x, float& y, float& z);

public:
	~Mat4();
	// Matrix creation.
	friend Mat4 S3DMath::ZeroMatrix();
	friend Mat4 S3DMath::IdentityMatrix();
	friend void S3DMath::IdentityMatrix(Mat4& mat);
	friend Mat4 S3DMath::ArbitraryMatrix(float (*mat4)[4*4]);

	// 
	friend Mat4 S3DMath::TranslationMatrix(float&& x, float&& y, float&& z);
	friend Mat4 S3DMath::TranslationMatrix(float& x, float& y, float& z);
	friend void S3DMath::TranslationMatrix(Mat4& mat, float&& x, float&& y, float&& z);
	friend void S3DMath::TranslationMatrix(Mat4& mat, float& x, float& y, float& z);
	
	friend Mat4 S3DMath::ScalingMatrix(float&& x, float&& y, float&& z);
	friend Mat4 S3DMath::ScalingMatrix(float& x, float& y, float& z);
	friend void S3DMath::ScalingMatrix(Mat4& mat, float&& x, float&& y, float&& z);
	friend void S3DMath::ScalingMatrix(Mat4& mat, float& x, float& y, float& z); 
	friend Mat4 S3DMath::ArbitraryScaleMatrix(const Vec3& direction, float& scaleFactor);
	friend Mat4 S3DMath::ArbitraryScaleMatrix(const Vec3& direction, float&& scaleFactor);

	// Rotations.
	friend Mat4 S3DMath::ArbitraryRotation(Vec3& axis, float& theta);
	friend Mat4 S3DMath:: ArbitraryRotation(Vec3& axis, float&& theta);
	friend Mat4 S3DMath::RotateXAxis(float& theta);
	friend Mat4 S3DMath::RotateXAxis(float&& theta);
	friend Mat4 S3DMath::RotateYAxis(float& theta);
	friend Mat4 S3DMath::RotateYAxis(float&& theta);
	friend Mat4 S3DMath::RotateZAxis(float& theta);
	friend Mat4 S3DMath::RotateZAxis(float&& theta);

	//Projections.
	friend Mat4 S3DMath::OrthoProjectionMat(Vec3& dir);

	Mat4 Multiply(const Mat4& other) const;
	Vec4& Multiply(Vec4& vec4) const;

	// Operator overloads.
	Mat4& operator=(const Mat4& other);
	Mat4& operator=(const float (*mat)[4*4]);

	friend Mat4 operator*(const Mat4& lhs, const Mat4& rhs);
	friend Vec4& operator*(const Mat4& lhs, Vec4& rhs);
	friend Mat4& operator*=(Mat4& lhs, const Mat4& rhs);
	friend bool operator==(const Mat4 lhs, const Mat4 rhs);
	friend bool operator!=(const Mat4 lhs, const Mat4 rhs);

	friend std::ostream& operator<<(std::ostream& out, const Mat4& mat);
}; 





