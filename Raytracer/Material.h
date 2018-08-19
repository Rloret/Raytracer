#pragma once

#include "Ray.h"
#include "Collidable.h"
#include "Vector3.h"

class HitInformation;

class Material
{
public:
	virtual bool scatterRay(Ray& r_in, HitInformation& hitinfo, Vector3& Attenuation, Ray& r_out) const =0;

	virtual Vector3 emitted(float u, float v, const Vector3& p) const{
		return Vector3(0);
	}
	enum TypeMat
	{
		NOSHADOWS, SHADOWS
	};

	TypeMat matType = NOSHADOWS;
};


