#pragma once

#include <math.h>
// #include "Mat4.h"

namespace S3DMath {
	const float PI = 3.14159265358979323846264338327;
	const float HALF_PI = PI / 2.0f;
	const float	TWO_PI = 2.0f * PI;
	const float TWO_PI_INV = 1.0f / TWO_PI;
	
	inline float ToRadians(float& degrees);
	inline float ToRadians(float&& degrees);
	// float Sine(float degrees);
}

float S3DMath::ToRadians(float& degrees)
{
	return (degrees / 180) * PI;
}

float S3DMath::ToRadians(float&& degrees)
{
	return (degrees / 180) * PI;
}
