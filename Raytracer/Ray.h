#pragma once

#include "Vector3.h"

class Ray
{
public:
	Ray() {}
	Ray( Vector3& a,  Vector3& b) { O = a; D = b; }

	Vector3 Origin() const { return O; }
	Vector3 Direction() const { return D; }
	Vector3 GetPoint(float t) const { return O + D*t; }
	
	Vector3 O;
	Vector3 D;
};

