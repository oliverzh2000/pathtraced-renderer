//
// Created by Oliver Zhang on 2020-12-28.
//

#include <iostream>
#include <memory>
#include "main_window.h"


int main() {
    std::unique_ptr<MainWindow> window = std::make_unique<MainWindow>("Pathtraced Renderer");

    while (!window->hasClosed()) {
        window->update();
    }

    return 0;
}