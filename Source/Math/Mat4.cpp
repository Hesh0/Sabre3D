#include "../Sabre3D/Sabre3Dstd.h"
#include "Mat4.h"



 // Flags that tell constructor what type oof matrix to construct.
const Mat4::Matflag TRANSLATION_MATRIX = 0x01;
const Mat4::Matflag SCALING_MATRIX = 0x02;


Mat4::Mat4(float&& val) : m_Matrix
	{ 
		DBG_NEW float[4 * 4]
		{
			val, 0.0f, 0.0f, 0.0f,
			0.0f, val, 0.0f, 0.0f,
			0.0f, 0.0f, val, 0.0f,
			0.0f, 0.0f, 0.0f, val
		}
	}
{
	S3D_ASSERT(m_Matrix != nullptr);
}

Mat4::Mat4(float& val) : m_Matrix
	{
		DBG_NEW float[4 * 4]
		{
			val, 0.0f, 0.0f, 0.0f,
			0.0f, val, 0.0f, 0.0f,
			0.0f, 0.0f, val, 0.0f,
			0.0f, 0.0f, 0.0f, val
		}
	}
{
	S3D_ASSERT(m_Matrix != nullptr);
}

Mat4::Mat4() : Mat4(1.0f) {}

Mat4::Mat4(float (*mat)[4*4])
{
	m_Matrix = DBG_NEW float[4 * 4];
	for (int i = 0; i < 4 * 4; i++)
		m_Matrix[i] = (*mat)[i];
}

Mat4::Mat4(const Matflag flag, float&& x, float&& y, float&& z)
{
	switch (flag)
	{
		case TRANSLATION_MATRIX:
			m_Matrix = DBG_NEW float[16]
			{
				1.0f, 0.0f, 0.0f, x,
				0.0f, 1.0f, 0.0f, y,
				0.0f, 0.0f, 1.0f, z,
				0.0f, 0.0f, 0.0f, 1.0f
			};
			break;
		case SCALING_MATRIX:
			m_Matrix = DBG_NEW float[4 * 4]
			{
				x, 0.0f, 0.0f, 0.0f,
				0.0f, y, 0.0f, 0.0f,
				0.0f, 0.0f, z, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			};
			break;
		// should really never reach here.
		default:
			break;
	}
}

Mat4::Mat4(const Matflag flag, float& x, float& y, float& z)
{
	switch (flag)
	{
	case TRANSLATION_MATRIX:
		m_Matrix = DBG_NEW float[16]
		{
			1.0f, 0.0f, 0.0f, x,
			0.0f, 1.0f, 0.0f, y,
			0.0f, 0.0f, 1.0f, z,
			0.0f, 0.0f, 0.0f, 1.0f
		};
		break;
	case SCALING_MATRIX:
		m_Matrix = DBG_NEW float[4 * 4]
		{
			x, 0.0f, 0.0f, 0.0f,
			0.0f, y, 0.0f, 0.0f,
			0.0f, 0.0f, z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
		break;
	default:
		break;
	}
}

Mat4::~Mat4()
{
	delete[] m_Matrix;
}

Mat4 Mat4::Multiply(const Mat4& other) const
{
	float sum;
	float mat[4 * 4]{0};
	
	for (int i = 0; i < 4; i++)
	{
		for (int row = 0; row < 4; row++)
		{
			sum = 0;
			for (int col = 0; col < 4; col++)
				sum += m_Matrix[col + i * 4] * other.m_Matrix[row + col * 4];
			mat[row + i * 4] = sum;
		}
	}

	return Mat4(&mat);
}

Vec4& Mat4::Multiply(Vec4& vec4) const 
{
	float sum;
	float temp[4];
	
	for (int row = 0; row < 4; row++)
	{
		sum = 0;
		for (int col = 0; col < 4; col++)
			sum += m_Matrix[col + row * 4] * vec4.vec4[col];
		temp[row] = sum;
	}
	vec4 = &temp;
	std::cout << vec4 << std::endl;
	
	return vec4;
}

Mat4 S3DMath::ZeroMatrix() 
{
	return Mat4(0.0f);
}

Mat4 S3DMath::IdentityMatrix() 
{
	return Mat4();
}

void S3DMath::IdentityMatrix(Mat4& mat)
{
	// Optimzation candidate.
	for (int col = 0; col < 4; col++)
	{
		for (int row = 0; row < 4; row++)
		{
			int i = row + col * 4;
			
			if (i % 5 == 0)
				mat.m_Matrix[i] = 1;
			else
				mat.m_Matrix[i] = 0;
		}
	}
}

Mat4 S3DMath::ArbitraryMatrix(float (*mat4)[4*4])
{
	return Mat4(mat4);
}

Mat4 S3DMath::TranslationMatrix(float&& x, float&& y, float&& z)
{
	return Mat4(TRANSLATION_MATRIX, x, y, z);
}

Mat4 S3DMath::TranslationMatrix(float& x, float& y, float& z)
{
	return Mat4(TRANSLATION_MATRIX, x, y, z);
}

void S3DMath::TranslationMatrix(Mat4& mat, float&& x, float&& y, float&& z)
{
	S3DMath::IdentityMatrix(mat);
	mat.m_Matrix[3] = x;
	mat.m_Matrix[7] = y;
	mat.m_Matrix[11] = z;
}

void S3DMath::TranslationMatrix(Mat4& mat, float& x, float& y, float& z)
{
	S3DMath::IdentityMatrix(mat);
	mat.m_Matrix[3] = x;
	mat.m_Matrix[7] = y;
	mat.m_Matrix[11] = z;
}

Mat4 S3DMath::ScalingMatrix(float && x, float && y, float && z)
{
	return Mat4(SCALING_MATRIX, x, y, z);
}

Mat4 S3DMath::ScalingMatrix(float& x, float& y, float& z)
{
	return Mat4(SCALING_MATRIX, x, y, z);
}

void S3DMath::ScalingMatrix(Mat4& mat, float && x, float && y, float && z)
{
	S3DMath::IdentityMatrix(mat);
	mat.m_Matrix[0] = x;
	mat.m_Matrix[5] = y;
	mat.m_Matrix[10] = z;
}

void S3DMath::ScalingMatrix(Mat4& mat, float& x, float& y, float& z)
{
	S3DMath::IdentityMatrix(mat);
	mat.m_Matrix[0] = x;
	mat.m_Matrix[5] = y;
	mat.m_Matrix[10] = z;
}

Mat4 S3DMath::ArbitraryScaleMatrix(const Vec3& direction, float&& scaleFactor)
{
	/* Vec3 n = direction.Normalize();
	float& k = scaleFactor;

	float mat[4 * 4] = {
		1 + (k - 1) * n.x*n.x, (k - 1) * n.x*n.y, (k - 1) * n.x*n.z,      0,
		(k - 1) * n.x*n.y,      1 + (k - 1) *n.y, (k - 1) * n.y*n.z,      0,
		(k - 1) * n.x*n.z,     (k - 1) * n.y*n.z,  1 + (k - 1) * n.z*n.z, 0,
		         0,                     0,                0,              1

	};

	return Mat4(&mat); */
	return S3DMath::ArbitraryScaleMatrix(direction, scaleFactor);
}

Mat4 S3DMath::ArbitraryScaleMatrix(const Vec3& direction, float & scaleFactor)
{
	Vec3 n = direction.Normalize();
	float& k = scaleFactor;

	float mat[4 * 4] = {
		1 + (k - 1) * n.x*n.x, (k - 1) * n.x*n.y,     (k - 1) * n.x*n.z,      0,
		(k - 1) * n.x*n.y,      1 + (k - 1) * n.y*n.y, (k - 1) * n.y*n.z,     0,
		(k - 1) * n.x*n.z,     (k - 1) * n.y*n.z,      1 + (k - 1) * n.z*n.z, 0,
		         0,                    0,                      0,             1
	};

	return Mat4(&mat);
}

Mat4 S3DMath::ArbitraryRotation(Vec3& axis, float& theta)
{
	Vec3 n = axis.Normalize();
	float thetaRad = S3DMath::ToRadians(theta);
	// TODO implement custom sin and cos functions.
	float cos0 = cos(thetaRad);
	if (theta == 90.0f) // Cos function gives -0 for 90 degree rotations, so change to 0.
		cos0 = -cos0;
	float sin0 = sin(thetaRad);

	float mat[4 * 4] = {
		n.x*n.x * (1 - cos0) + cos0,       n.x*n.y * (1 - cos0) + n.z * sin0, n.x*n.z * (1 - cos0) - n.y * sin0, 0,
		n.x*n.y * (1 - cos0) - n.z * sin0, n.y*n.y * (1 - cos0) + cos0,       n.y*n.z * (1 - cos0) + n.x * sin0, 0,
		n.x*n.z * (1 - cos0) + n.y* sin0,  n.y*n.z * (1 - cos0) - n.x * sin0, n.z*n.z * (1 - cos0) + cos0,       0,
		              0,                                0,                                0,                     1
	};

	return Mat4(&mat);
}

Mat4 S3DMath::ArbitraryRotation(Vec3& axis, float&& theta)
{
	return S3DMath::ArbitraryRotation(axis, theta);
}

Mat4 S3DMath::RotateXAxis(float& theta)
{
	float thetaRad = S3DMath::ToRadians(theta); 
	float sin0;
	float cos0;

#ifdef __GNUC__ 
	sincosf(thetaRad, &sin0, &cos0);
#else
	sin0 = sin(thetaRad);
	cos0 = cos(thetaRad);
#endif 
	if (theta == 90.0f)
		cos0 = -cos0;

	printf("theta = %.2f cos90 = %.2f, sin90 = %.2f\n", thetaRad, cos0, sin0);

	float mat[4 * 4] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cos0, sin0, 0.0f,
		0.0f,-sin0, cos0, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	return Mat4(&mat);
}

Mat4 S3DMath::RotateXAxis(float&& theta)
{
	float thetaRad = S3DMath::ToRadians(theta); 

	float cos0 = cos(thetaRad);
	if (theta == 90.0f)
		cos0 = -cos0;
	float sin0 = sin(thetaRad);

	printf("theta = %.2f cos90 = %.2f, sin90 = %.2f\n", thetaRad, cos0, sin0);

	float mat[4 * 4] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cos0, sin0, 0.0f,
		0.0f,-sin0, cos0, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	return Mat4(&mat);
}

Mat4 S3DMath::RotateYAxis(float& theta)
{
	float thetaRad = S3DMath::ToRadians(theta);

	float sin0 = sin(theta);
	float cos0 = cos(theta);
	if (theta == 90.0f)
		cos0 = -cos0;

	printf("theta = %.2f cos90 = %.2f, sin90 = %.2f\n", thetaRad, cos0, sin0);

	float mat[4 * 4] = {
		cos0, 0.0f,-sin0, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
	    sin0, 0.0f, cos0, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	return Mat4(&mat);
}

Mat4 S3DMath::RotateYAxis(float && theta)
{
	float thetaRad = S3DMath::ToRadians(theta);

	float sin0 = sin(thetaRad);
	float cos0 = cos(thetaRad);
	if (theta == 90.0f)
		cos0 = -cos0;

	printf("theta = %.2f cos90 = %.2f, sin90 = %.2f\n", thetaRad, cos0, sin0);

	float mat[4 * 4] = {
		cos0, 0.0f,-sin0, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		sin0, 0.0f, cos0, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	return Mat4(&mat);
}

Mat4 S3DMath::RotateZAxis(float& theta)
{
	float thetaRad = S3DMath::ToRadians(theta); 
	
	float sin0 = sin(thetaRad);
	float cos0 = cos(thetaRad);
	if (theta == 90.0f)
		cos0 = -cos0;

	printf("theta = %.2f cos90 = %.2f, sin90 = %.2f\n", thetaRad, cos0, sin0);

	float mat[4 * 4] = {
		cos0, sin0, 0.0f, 0.0f,
	   -sin0, cos0, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	return Mat4(&mat);
}

Mat4 S3DMath::RotateZAxis(float&& theta)
{
	float thetaRad = S3DMath::ToRadians(theta); 

	float sin0 = sin(thetaRad);
	float cos0 = cos(thetaRad);
	if (theta == 90.0f)
		cos0 = -cos0;

	printf("thetha = %.2f cos90 = %.2f, sin90 = %.2f\n", thetaRad, cos0, sin0);

	float mat[4 * 4] = {
		cos0, sin0, 0.0f, 0.0f,
		-sin0, cos0, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	return Mat4(&mat);
}

Mat4 S3DMath::OrthoProjectionMat(Vec3& axis)
{
	Vec3 n = axis.Normalize();
	
	float mat[4 * 4] = {
		1 - n.x*n.x, -n.x*n.y,   -n.x*n.z,     0, 
		-n.x*n.y,     1 -n.y*n.y, -n.y*n.z,    0,
		-n.x*n.z,    -n.y*n.z,   1 - n.z*n.z,  0,
		   0,            0,          0,        1
	};

	return Mat4(&mat);
}

Mat4& Mat4::operator=(const Mat4& other)
{
	for (int i = 0; i < 4 * 4; i++)
		this->m_Matrix[i] = other.m_Matrix[i];

	return *this;
}

Mat4& Mat4::operator=(const float (*mat)[4*4])
{
	for (int i = 0; i < 4 * 4; i++)
		this->m_Matrix[i] = (*mat)[i];

	return *this;
}

 #pragma region Mat4 friend operator overloads

Mat4 operator*(const Mat4& lhs, const Mat4& rhs)
{
	return lhs.Multiply(rhs);
}

Vec4& operator*(const Mat4& lhs, Vec4& rhs)
{
	return lhs.Multiply(rhs);
}

Mat4& operator*=(Mat4& lhs, const Mat4& rhs)
{
	float sum{0.0f};
	float mat[4 * 4]{0};
	
	for (int i = 0; i < 4; i++)
	{
		for (int row = 0; row < 4; row++)
		{
			sum = 0.0f;
			for (int col = 0; col < 4; col++)
				sum += lhs.m_Matrix[col + i * 4] * rhs.m_Matrix[row + col * 4];
			mat[row + i * 4] = sum;
		}
	}
	lhs = &mat;

	return lhs;
}

bool operator==(const Mat4 lhs, const Mat4 rhs)
{
	return false;
}

bool operator!=(const Mat4 lhs, const Mat4 rhs)
{
	return false;
}

std::ostream& operator<<(std::ostream& out, const Mat4& mat)
{
	for (int i = 0; i < 16; i += 4)
		out << "[" << precision(6) << mat.m_Matrix[i] << ", " << mat.m_Matrix[i + 1] << ", " << mat.m_Matrix[i + 2] << ", " << mat.m_Matrix[i + 3] << "]\n";
	
	return out;
}

#pragma endregion