
#include "ObstacleWarnings.hpp"
#include "threepp/loaders/FontLoader.hpp"
#include "threepp/extras/imgui/ImguiContext.hpp"
#include "threepp/math/Color.hpp"
//#include "threepp/extras/monitor.hpp"
#include <iostream>


using namespace threepp;

ObstacleWarning::ObstacleWarning(const std::string& message, float fadeDuration, float initialOpacity)
        : message_(message), fadeDuration_(fadeDuration), opacity_(initialOpacity) {
}

std::shared_ptr<Text2D> ObstacleWarning::getWarningText(){
    // Load font and set up 2D text


    //std::string message = "Morten is very handsome";
    const auto font = fontLoader_.defaultFont();
    TextGeometry::Options opts(font, 40 * monitor::contentScale().first);

    hudText_ = std::make_shared<Text2D>(opts, message_);
    hudText_->setColor(Color::red);
    //Is always going to be between 1 and 0
    hudText_->material()->opacity = opacity_;
    hudText_->layers.set(hudLayer_);

    return hudText_;
}


void enableHudCamera(){
    auto hudCamera = OrthographicCamera::create(-1, 1, 1, -1, 0, 1);
    hudCamera->layers.enable(1);
}


void ObstacleWarning::update(float deltaTime) {
    if (opacity_ > 0) {
        opacity_ -= deltaTime / fadeDuration_;
        if (opacity_ < 0) {
            opacity_ = 0;
            removeWarning();
        }
        hudText_->material()->opacity = opacity_;
    }
}

void ObstacleWarning::showWarning() {
    opacity_ = 1.0f;
    hudText_->material()->opacity = opacity_;
}

void ObstacleWarning::removeWarning() {
    hudText_->material()->opacity = 0;  // Hide the text
}