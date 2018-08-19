#pragma once
#include "Vector3.h"

class Light {


public:
	Light(Vector3 P,Vector3 I, Vector3 A) :position(P) ,Attenuation(A), Intensity(I){}

	Vector3 getLightIntensity(float distance){
		float k = (1.0f / (1 + Attenuation.y *distance + Attenuation.z *distance*distance));
		return Intensity * k;
	}

	Vector3 position;
	Vector3 Attenuation;
	Vector3 Intensity;


};