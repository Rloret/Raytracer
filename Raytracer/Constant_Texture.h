#pragma once

#include "Texture.h"
class Constant_Texture : public Texture {
public:
	Constant_Texture() {};
	Constant_Texture(Vector3 c): color(c) {};

	Vector3 color;


	// Inherited via Texture
	virtual Vector3 value(float u, float v, const Vector3 & p) const override {
		return color;
	}

};