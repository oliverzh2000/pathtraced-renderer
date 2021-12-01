//
// Created by Oliver Zhang on 2021-11-28.
//

#ifndef PATHTRACED_RENDERER_FPS_COUNTER_H
#define PATHTRACED_RENDERER_FPS_COUNTER_H

#include <deque>

class FPSCounter {
    std::deque<double> frameTimes;

public:
    int frameTimesToKeep;
    double secondsInAverage; // Average this long of most recent frame times.

public:
    FPSCounter(int frameTimesToKeep, int secondsInAverage)
        : frameTimesToKeep(frameTimesToKeep), secondsInAverage(secondsInAverage) {};

    void finishFrame();

    // Average frome time in seconds.
    // Average is computed over the secondsInAverage most recent frame times.
    double averageFrameTime() const;

    const std::deque<double> &getFrameTimes() const;
};


#endif //PATHTRACED_RENDERER_FPS_COUNTER_H
