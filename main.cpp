//
// Created by Oliver Zhang on 2020-12-28.
//

#include <iostream>
#include <memory>
#include "window.h"


int main() {
    std::unique_ptr<Window> window = std::make_unique<Window>("Zhang Physically based flight simulator");

    while (!window->hasClosed()) {
        window->update();
    }

    return 0;
}