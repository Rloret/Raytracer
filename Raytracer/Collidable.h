#pragma once

#include "Vector3.h"
#include "Ray.h"
#include "Material.h"

class Material;

 struct HitInformation {
	float t;
	Vector3 Point;
	Vector3 Normal;
	Vector3 UV;
	Material* Surface_Mat;

};
class ICollidable {
public:
	virtual bool IntersectedBy(const Ray& r,float min, float max, HitInformation& hitInfo)=0;
};
