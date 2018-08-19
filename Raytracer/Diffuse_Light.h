#pragma once
#include "Material.h"
#include "Texture.h"
class Diffuse_Light : public Material {
public:
	Diffuse_Light(Texture*a) : Emission(a) {};


	// Inherited via Material
	virtual bool scatterRay(Ray & r_in, HitInformation & hitinfo, Vector3 & Attenuation, Ray & r_out) const override {
		return false;
	};

	virtual Vector3 emitted(float u, float v, const Vector3 & p) const {
		return Emission->value(u,v,p);
	}


	Texture* Emission;

	

};
