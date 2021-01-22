//
// Created by Oliver Zhang on 2020-12-31.
//

#ifndef PATHTRACED_FLIGHT_SIM_QUAD_RENDERER_H
#define PATHTRACED_FLIGHT_SIM_QUAD_RENDERER_H

#include "shader.h"
#include "geometry.h"

class QuadRenderer {
private:
    Shader shader;
    GLuint VAO;
    GLuint texture;
	int width, height;
    float* imgData = nullptr;
    const int bytesPerChannel = sizeof(float); // 32 bit float.

public:
    const int numChannels = 3; // rgb.
    int samplesPerPixel = 0;
    float exposure = 1.0;

public:
	QuadRenderer(int width, int height);

	/*
	 * Upload the data currently in the internal pixel buffer to the GPU.
	 */
	void upload();

	/*
	 * Draw data in GPU to screen.
	 */
    void render();

    /*
     * Reinitialize the internal pixel buffer to be the new size, if the given size is not equal to current size.
     */
	void setSize(int newWidth, int newHeight);
	
	[[nodiscard]] int getWidth() const { return width; };
	[[nodiscard]] int getHeight() const { return height; };

	void writePixel(int row, int col, Color color);

	/*
	 * Similar to writePixel, but add instead of setting color.
	 */
	void accumulatePixel(int row, int col, Color color);

	/*
	 * Get a copy of the image data after division by samples per pixel.
	 */
	const float *scaledImgDataCopy() const;
};


#endif //PATHTRACED_FLIGHT_SIM_QUAD_RENDERER_H
