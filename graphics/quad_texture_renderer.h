//
// Created by Oliver Zhang on 2020-12-31.
//

#ifndef PATHTRACED_FLIGHT_SIM_QUAD_TEXTURE_RENDERER_H
#define PATHTRACED_FLIGHT_SIM_QUAD_TEXTURE_RENDERER_H

#include "shader.h"

class QuadRenderer {
private:
    Shader shader;
    GLuint VAO;
    GLuint texture;
	int frameCount = 0;

public:
    QuadRenderer();

    void renderRGBImage(int width, int height, unsigned char *data);

	int getFrameCount() { return frameCount; };
};


#endif //PATHTRACED_FLIGHT_SIM_QUAD_TEXTURE_RENDERER_H
