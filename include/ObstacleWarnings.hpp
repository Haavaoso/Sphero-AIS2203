//
// Created by hanur on 21.10.2024.
//

#ifndef SPHEROSIM_OBSTACLEWARNINGS_H
#define SPHEROSIM_OBSTACLEWARNINGS_H

#include <string>
#include <memory>
#include <threepp/threepp.hpp>

#include <string>
#include <threepp/threepp.hpp>
#include <threepp/extras/imgui/ImguiContext.hpp>

class ObstacleWarning {
public:
    ObstacleWarning(const std::string& message, float fadeDuration, float initialOpacity);

    void update(float deltaTime);
    void showWarning();
    void removeWarning();
    void enableHudCamera();
    std::shared_ptr<threepp::Text2D> getWarningText();

private:
    std::string message_;
    float fadeDuration_;
    float opacity_;
    std::shared_ptr<threepp::Text2D> hudText_;
    threepp::FontLoader fontLoader_;
    const int hudLayer_ = 0;
};

#endif //SPHEROSIM_OBSTACLEWARNINGS_H
