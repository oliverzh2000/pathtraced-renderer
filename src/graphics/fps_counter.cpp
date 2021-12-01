//
// Created by Oliver Zhang on 2021-11-28.
//

#include "fps_counter.h"

#include <GLFW/glfw3.h>

void FPSCounter::finishFrame() {
    static double lastTime = 0;
    if (lastTime != 0) { // skip on first time
        double elapsed = glfwGetTime() - lastTime;
        frameTimes.push_front(elapsed);
        if (frameTimes.size() > frameTimesToKeep) {
            frameTimes.pop_back();
        }
    }
    lastTime = glfwGetTime();
}

double FPSCounter::averageFrameTime() const {

    double totalFrameTimes = 0;
    int numFrames = 0;
    for (double frameTime : frameTimes) {
        totalFrameTimes += frameTime;
        numFrames++;
        if (totalFrameTimes > secondsInAverage) {
            break;
        }
    }
    return totalFrameTimes / numFrames;
}

const std::deque<double> &FPSCounter::getFrameTimes() const {
    return frameTimes;
}