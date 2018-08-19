#pragma once

#include "Material.h"
#define RAND01 ((double)rand() / (RAND_MAX))

class Dielectric :public Material {
	public:
	Dielectric(float refractiveIndex) :r_index(refractiveIndex) {};
	float r_index;

	float schlick(float cosine, float ref_ind)const {
			float r0 = (1 - ref_ind) / (1 + ref_ind);
			r0 = r0*r0;
			return r0 + (1 - r0)* pow((1 - cosine), 5);

		
	}
		// Inherited via Material
	virtual bool scatterRay(Ray & r_in, HitInformation & hitinfo, Vector3 & Attenuation, Ray & r_out) const override {
		Vector3 outward_normal;
		Vector3 reflected = Vector3::Reflect(r_in.Direction(), hitinfo.Normal);
		Vector3 refracted;

		float cosine;
		float aux_ref_index;
		float reflect_prob;
		Attenuation = Vector3(1.0, 1.0,1.0);

		//determinamos si el choque es interior o exterior al material
		if (r_in.Direction()*hitinfo.Normal > 0) {
			outward_normal = hitinfo.Normal*-1;
			aux_ref_index = r_index;
			cosine = r_index * (r_in.Direction() * hitinfo.Normal) / r_in.Direction().module();
		}
		else {
			outward_normal = hitinfo.Normal;
			aux_ref_index = 1.0 / r_index;
			cosine = -1* (r_in.Direction() * hitinfo.Normal) / r_in.Direction().module();

		}
		//una vez calculados los valores acorde al tipo de contacto, determinamos si el rayo se puede refractar o no
		if (Vector3::Refract(r_in.Direction(), outward_normal, aux_ref_index, refracted)) {
			reflect_prob = schlick(cosine, this->r_index);
			
		}
		else {
			reflect_prob = 1.0;
			
		}
		// y en funcion de un aleatorio determinamos si finalmente refracta
		if (RAND01 < reflect_prob) {
			r_out = Ray(hitinfo.Point, reflected);
		}
		else
		{
			r_out = Ray(hitinfo.Point, refracted);

		}

		
		return true;

	}


};