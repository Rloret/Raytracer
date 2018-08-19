#pragma once

#include <iostream>
#include "Material.h"
#include "Vector3.h"
#include "Light.h"
#include "Collidable.h"
#include "Texture.h"
class Phong : public Material {
public:
	Phong(Texture* A,Texture* S,float shinni,Light** Lights, int numLights,ICollidable *geometry)  {
		this->albedo = A;
		this->specular = S;
		this->Lights = Lights;
		this->geometry = geometry;
		this->shininess = shinni;
		this->numLights = numLights;
		matType = SHADOWS;
	};

	//We are using this since we are maintaining the structure, however
	//we return a ray to infinity to let our raytracer know that this ray does not rebound and thus
	//it should end the tracing there
	virtual bool scatterRay(Ray & r_in, HitInformation & hitinfo, Vector3& Attenuation, Ray & r_out) const override {

		Vector3 Origin = hitinfo.Point;
		Vector3 target = Origin + hitinfo.Normal.normalized() + Vector3::Random_In_Sphere_Volume();
		r_out = Ray(Vector3(FLT_MAX), Vector3(FLT_MAX)); // ray at infinity to infinity
		Attenuation = shade(hitinfo.Normal.normalized(),hitinfo.Point,hitinfo.UV.x,hitinfo.UV.y,albedo,specular); // using Phongs model
		return true;
	}

	//In this bit we are determining the surface color of the surface using phongs brdf
	Vector3 shade(Vector3 N, Vector3 P,float u, float v,Texture* albedo, Texture* specular )const {

		Vector3 Kd = Vector3(0);
		Vector3 Ks = Vector3(0);
	
		Vector3 R;

		for (int i = 0; i < numLights; i++)
		{
			Light* iLight = Lights[0];

			Vector3 L = iLight->position - P;
			float length = L.module();
			Vector3 I = iLight->getLightIntensity(length);
			L = L.normalized();

			Ray ShadowRay = Ray(P + L * 1e-2, L);
			HitInformation auxInfo ;
			
			if (geometry->IntersectedBy(ShadowRay, 0.01, FLT_MAX - 1, auxInfo) && auxInfo.Surface_Mat->matType ==SHADOWS ) {
				return Vector3(0, 0, 0);
			}

			float NdotL = N*(L);
			R = Vector3::Reflect((L*-1),N);
			float dotRV = R.normalized()*(P.normalized() *-1);
			Vector3 c;
			
			Kd += (Vector3::componentWiseMult(I,albedo->value(u,v,P) )*NdotL).Clamp(0.0f, 1.0f);
			Ks = Ks + Vector3::componentWiseMult(I,specular->value(u,v,P))* pow(fmaxf(dotRV, 1e-6), shininess)*NdotL;


		}
		return Kd +Ks;
	}

	//Variables
	Texture* albedo;
	Texture* specular;
	float shininess;
	Light** Lights;
	ICollidable* geometry;
	int numLights;


};

