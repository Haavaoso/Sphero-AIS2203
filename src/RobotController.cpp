//
// Created by havso on 15/10/2024.
//

#include "RobotController.hpp"

#include <iostream>

void RobotController::onKeyPressed(threepp::KeyEvent evt) {
    switch (evt.key) {
        case threepp::Key::Q:
            std::cout << "DAAAMN" << std::endl;
            dir_.LEFT_ALT = true;
            break;
        case threepp::Key::A:
            dir_.LEFT = true;
            break;
        case threepp::Key::W:
            dir_.FWD = true;
            break;
        case threepp::Key::S:
            dir_.REV = true;
            break;
        case threepp::Key::E:
            dir_.RIGHT_ALT = true;
            break;
        case threepp::Key::D:
            dir_.RIGHT = true;
            break;
    }
}

void RobotController::onKeyReleased(threepp::KeyEvent evt) {
    switch (evt.key) {
        case threepp::Key::Q:
            dir_.LEFT_ALT = false;
            break;
        case threepp::Key::A:
            dir_.LEFT = false;
            break;
        case threepp::Key::W:
            dir_.FWD = false;
            break;
        case threepp::Key::S:
            dir_.REV = false;
            break;
        case threepp::Key::E:
            dir_.RIGHT_ALT = false;
            break;
        case threepp::Key::D:
            dir_.RIGHT = false;
            break;
    }
}

std::tuple<int8_t, int8_t, int8_t, int8_t> RobotController::controllerOut() {
    if (dir_.modeTank) {
        threepp::Vector4 track;
        if (dir_.RIGHT_ALT) {
            track.x = 1;
        } else if (dir_.RIGHT) {
            track.x = 2;
        } else {
            track.x = 0;
        }
        if (dir_.LEFT_ALT) {
            track.y = 1;
        } else if (dir_.LEFT) {
            track.y = 2;
        } else {
            track.y = 0;
        }
        return std::make_tuple(track.y, speed_, track.x, speed_);
    }
    // Add else case if needed for non-tank mode.
    return std::make_tuple(0, 0, 0, 0); // Placeholder
}

DIR RobotController::getWASD() {
    return dir_;
}

void RobotController::update() {
    if (dir_.FWD) {
        speed_ += speedIncrement;
    }
    if (dir_.REV) {
        speed_ -= speedIncrement;
    }
}

