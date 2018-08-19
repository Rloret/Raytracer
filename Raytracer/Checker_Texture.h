#pragma once
#include "Texture.h"
class Checker_Texture : public Texture {
	public:
	Checker_Texture() {};
	Checker_Texture( Texture* t0, Texture* t1 ): even(t0), odd(t1){};


	Texture* even;
	Texture* odd;

	// Inherited via Texture
	virtual Vector3 value(float u, float v, const Vector3 & p) const override {
		float sineSeries = sin(10 * p.x) *sin(10 * p.y) *sin(10 * p.z);
		if (sineSeries < 0) {
			return odd->value(u, v, p);
		}
		else
		{
			return even->value(u, v, p);
		}
	};
};