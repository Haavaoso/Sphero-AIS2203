

#include "SpheroRobot.hpp"
#include <cmath>

SpheroRobot::SpheroRobot() : virtualCamera(100, 1) {
    auto mainBody = createMainBody();
    auto leftTrack = createTrack(9);
    auto rightTrack = createTrack(-9);
    auto leftBelt = createBelt(9);
    auto rightBelt = createBelt(-9);

    Object3D::add(mainBody);
    Object3D::add(leftTrack);
    Object3D::add(rightTrack);
    Object3D::add(leftBelt);
    Object3D::add(rightBelt);
    virtualCamera.position.set(0, 9, 5);
    virtualCamera.rotateY(threepp::math::PI);
    virtualCamera.rotateX(threepp::math::PI / -8);

    Object3D::add(virtualCamera);
}

void SpheroRobot::drive_raw(uint8_t leftMode, uint8_t leftSpeed, uint8_t rightMode, uint8_t rightSpeed) {
    // Left motor
    if (leftMode == 1) {
        leftMotorSpeed_ = leftSpeed;  // Forward
    } else if (leftMode == 2) {
        leftMotorSpeed_ = -leftSpeed; // Reverse
    } else {
        leftMotorSpeed_ = 0;  // Off
    }

    // Right motor
    if (rightMode == 1) {
        rightMotorSpeed_ = rightSpeed;  // Forward
    } else if (rightMode == 2) {
        rightMotorSpeed_ = -rightSpeed; // Reverse
    } else {
        rightMotorSpeed_ = 0;  // Off
    }
}

void SpheroRobot::drive_with_heading(uint8_t speed, uint16_t heading, uint8_t flags) {
    // Implementation can be added here if needed
}

void SpheroRobot::reset_yaw() {
    this->rotation.y = 0;
}

threepp::PerspectiveCamera& SpheroRobot::getVirtualCamera() {
    return virtualCamera;
}

void SpheroRobot::update(float deltaTime) {
    float v = (rightMotorSpeed_ + leftMotorSpeed_) / 2.0f;
    float omega = (rightMotorSpeed_ - leftMotorSpeed_) / wheelBase_;

    orientation_ += omega * deltaTime;

    float deltaX = v * deltaTime * std::cos(orientation_);
    float deltaZ = v * deltaTime * std::sin(orientation_);
    position_.x += deltaX;
    position_.z += deltaZ;

    // Update the Object3D's position and rotation
    this->position.set(position_.x, position_.y, position_.z);
    this->rotation.y = -(orientation_ + threepp::math::PI / 2);
}

std::shared_ptr<threepp::Mesh> SpheroRobot::createMainBody() {
    auto geometry = threepp::BoxGeometry::create(14, 6.5, 18);
    auto material = threepp::MeshBasicMaterial::create();
    material->color = threepp::Color::darkslategray;
    auto mesh = threepp::Mesh::create(geometry, material);
    mesh->position.set(0, 6.5 / 2, 0);  // Set the position of the body
    return mesh;
}

std::shared_ptr<threepp::Mesh> SpheroRobot::createTrack(float xOffset) {
    auto geometry = threepp::BoxGeometry::create(4, 6, 18);
    auto material = threepp::MeshBasicMaterial::create();
    material->color = threepp::Color::antiquewhite;
    auto mesh = threepp::Mesh::create(geometry, material);
    mesh->position.set(xOffset, 6 / 2, 0);  // Position left or right track's x-offset
    return mesh;
}

std::shared_ptr<threepp::Mesh> SpheroRobot::createBelt(float xOffset) {
    auto geometry = threepp::BoxGeometry::create(3.2, 6.3, 18.1);
    auto material = threepp::MeshBasicMaterial::create();
    material->color = threepp::Color::gray;
    auto mesh = threepp::Mesh::create(geometry, material);
    mesh->position.set(xOffset, 6.3 / 2, 0);  // Position belt's x-offset
    return mesh;
}