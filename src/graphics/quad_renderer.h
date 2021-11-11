//
// Created by Oliver Zhang on 2020-12-31.
//

#ifndef PATHTRACED_RENDERER_QUAD_RENDERER_H
#define PATHTRACED_RENDERER_QUAD_RENDERER_H

#include "shader.h"
#include "geometry.h"

class QuadRenderer {
private:
    Shader shader;
    GLuint VAO;
    GLuint textureID;
	int width, height;
    float* data = nullptr;
    const int bytesPerChannel = sizeof(float); // 32 bit float.

public:
    const int numChannels = 3; // rgb.
    float exposure = 1.0;
    int samplesPerPixel = 0;

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
     * Save the image data to file in the radiance HDR format.
     */
    void saveHdrFile();

    /*
     * Reinitialize the internal pixel buffer to be the new size, if the given size is not equal to current size.
     */
	void setSize(int newWidth, int newHeight);
	
	int getWidth() const { return width; };
	int getHeight() const { return height; };

	void writePixel(int row, int col, Color color);

	/*
	 * Similar to writePixel, but add instead of setting color.
	 * This allows a progressive rendering technique analogous to a long exposure in a physical camera.
	 */
	void accumulatePixel(int row, int col, Color color);

	/**
	 * Increment the internal samples per pixel counter.
	 */
	void finishAcculumatingFrame() {
	    samplesPerPixel++;
	}

	/*
	 * Zero out image data array and set samples per pixel to 0.
	 * Call this whenever scene data changes, unless of course you want to achieve a long exposure effect over multiple frames.
	 */
	void reset();

	/*
	 * Get a copy of the image data after division by samples per pixel.
	 */
	const float *scaledData() const;
};


#endif //PATHTRACED_RENDERER_QUAD_RENDERER_H
