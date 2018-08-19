#pragma once


#include "Collidable.h"
#include "Material.h"
class Sphere : public ICollidable
{
public:
	Sphere(Vector3 Center, float R,Material* surfaceMaterial);
	bool IntersectedBy(const Ray& r, float min, float max, HitInformation& hitInfo) override;
	Vector3 ComputeUV(HitInformation& h);
private:
	Vector3 center;
	float radius;
	Material* sphereMaterial;
};



inline Sphere::Sphere(Vector3 Center, float R,Material* surfaceMat)
{
	this->center = Center;
	this->radius = R;
	this->sphereMaterial = surfaceMat;
}

//Extracted from Peter Shirley's books of ray tracing
inline bool Sphere::IntersectedBy(const Ray & r, float min, float max, HitInformation& hitInfo)
{
	Vector3 OC = r.O - this->center;
	float a = r.D*r.D;
	float b = (OC*r.D);
	float c = (OC*OC) - (radius*radius);
	float discriminant = b*b - a*c;

	if (discriminant > 0) {
		float val = (-b - sqrt(discriminant)) / a;
		if (val<max && val>min) {
			hitInfo.t = val;
			hitInfo.Point = r.GetPoint(val);
			hitInfo.Normal = (hitInfo.Point - this->center) / radius;
			hitInfo.Surface_Mat = this->sphereMaterial;
			hitInfo.UV = ComputeUV(hitInfo);
			return true;
		}
		val = (-b + sqrt(discriminant)) / a;
		if (val<max && val>min) {
			hitInfo.t = val;
			hitInfo.Point = r.GetPoint(val);
			hitInfo.Normal = (hitInfo.Point - this->center) / radius;
			hitInfo.Surface_Mat = this->sphereMaterial;
			hitInfo.UV = ComputeUV(hitInfo);


			return true;
		}
	}
	return false;

}

Vector3 Sphere::ComputeUV(HitInformation& h) {
	//Calculating the texture coordinate for a sphere

	float u = asin(h.Normal.x) / M_PI + 0.5;
	float v = asin(h.Normal.y) / M_PI + 0.5;
	

	return Vector3(u, v, 0);
}
