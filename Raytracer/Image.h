#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//Class that holds the information loaded from stb.
class Image {
public:
	Image(const char* filename) {
		
		tex_data = stbi_load(filename, &width, &height, &linealSize, 0);
	 }

	int width;
	int height;
	int linealSize;
	unsigned char *tex_data;
};