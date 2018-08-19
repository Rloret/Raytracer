#pragma once
#include "Texture.h"
class Image_Texture : public Texture {
public :
	Image_Texture() {};
	Image_Texture(unsigned char* pixels, int W, int H): data(pixels), width(W), height(H) {};

	// Inherited via Texture
	virtual Vector3 value(float u, float v, const Vector3 & p) const override {
		int i = u * width;
		int j = (1-v)*height -0.001;

		i = i < 0 ? 0 : i>width-1?width-1:i;
		j = j < 0 ? 0 : j>height - 1 ? height - 1 :j;

		float r = int(data[3 * i + 3 * width*j]) / 255.0;
		float g = int(data[3 * i + 3 * width*j+1]) / 255.0;
		float b = int(data[3 * i + 3 * width*j+2]) / 255.0;

		return Vector3(r, g, b);

	}
	unsigned char* data;
	int width, height;

};