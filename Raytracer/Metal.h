#pragma once
#include "Material.h"
#include "Vector3.h"

class Metal : public Material {
public:
	Metal(Vector3 A, float roughness) :albedo(A) { this->roughness = roughness > 1 ? 1 : roughness; };
	Vector3 albedo;
	float roughness;

	// Inherited via Material
	virtual bool scatterRay(Ray & r_in, HitInformation & hitinfo, Vector3& Attenuation, Ray & r_out) const override {
		Vector3 reflectedDir = Vector3::Reflect(r_in.D.normalized(), hitinfo.Normal);

		r_out = Ray(hitinfo.Point, reflectedDir+ Vector3::Random_In_Sphere_Volume()*roughness);
		Attenuation = albedo;
		return (r_out.Direction() * hitinfo.Normal) > 0;
	}
};