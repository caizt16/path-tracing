// Canvas and color space manipulations.

#ifndef _RENDER_CANVAS_H
#define _RENDER_CANVAS_H

#include "utils.h"

class Canvas {
public:
	int width, height, size;
	Real gain;
	Color* pixels;
	// This variable accumulates the total number of passes that have contributed to a particular pixel.
	// This is critical for tiled rendering, where different numbers of passes may have contributed to different pixels.
	int* per_pixel_passes;
	Real* depth_buffer;

	Canvas(int width, int height);
	~Canvas();
	void zero();
	Color* pixel_ptr(int x, int y);
	int* per_pixel_passes_ptr(int x, int y);
	Real* depth_ptr(int x, int y);
	void get_pixel(int x, int y, uint8_t* dest);
	void add_from(Canvas* other);
	int save(std::string path);
};

#endif

