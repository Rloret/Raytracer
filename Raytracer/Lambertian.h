#pragma once
#include "Vector3.h"
#include "Material.h"
#include <iostream>
#include "Texture.h"

class Lambertian : public Material {
public:
	Lambertian(Texture* A) :albedo(A) {
		this->matType = SHADOWS;
	};
	virtual bool scatterRay(Ray & r_in, HitInformation & hitinfo, Vector3& Attenuation, Ray & r_out) const override {
	
		Vector3 Origin = hitinfo.Point;
		Vector3 target = Origin + hitinfo.Normal.normalized() + Vector3::Random_In_Sphere_Volume();
		r_out = Ray(Origin , target - Origin );
		Attenuation =  albedo->value(hitinfo.UV.x, hitinfo.UV.y, hitinfo.Point);
		return true;
	}

	Texture* albedo;

	
};


