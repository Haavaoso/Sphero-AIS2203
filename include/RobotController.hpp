//
// Created by havso on 15/10/2024.
//

#include <iostream>

#include "threepp/threepp.hpp"
#include <tuple>
#ifndef KEYBOARD_INPUT_HPP
#define KEYBOARD_INPUT_HPP

#include "threepp/threepp.hpp"
#include <tuple>

struct DIR {
    bool modeTank = true;
    bool FWD = false;
    bool REV = false;
    bool LEFT_ALT = false;
    bool LEFT = false;
    bool RIGHT_ALT = false;
    bool RIGHT = false;
};

class RobotController : public threepp::KeyListener {
public:
    void onKeyPressed(threepp::KeyEvent evt) override;
    void onKeyReleased(threepp::KeyEvent evt) override;
    std::tuple<int8_t, int8_t, int8_t, int8_t> controllerOut();
    DIR getWASD();
    void update();

private:
    DIR dir_;
    uint8_t speed_ = 100;
    int speedIncrement = 1;
};

#endif //KEYBOARD_INPUT_HPP
