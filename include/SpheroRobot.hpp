#ifndef SPHEROROBOT_HPP
#define SPHEROROBOT_HPP

#include <cstdint>
#include "threepp/cameras/PerspectiveCamera.hpp"
#include "threepp/core/Object3D.hpp"
#include "threepp/geometries/BoxGeometry.hpp"
#include "threepp/materials/MeshBasicMaterial.hpp"
#include "threepp/math/MathUtils.hpp"
#include "threepp/math/Vector3.hpp"
#include "threepp/objects/Mesh.hpp"

class SpheroRobot : public threepp::Object3D {
public:
    SpheroRobot() : virtualCamera(100, 1) {
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
        virtualCamera.rotateX(threepp::math::PI/-8);


        Object3D::add(virtualCamera);


    }

    void drive_raw(uint8_t leftMode, uint8_t leftSpeed, uint8_t rightMode, uint8_t rightSpeed) {
        // Left motor
        if (leftMode == 1) {
            // Forward
            leftMotorSpeed_ = leftSpeed;
        } else if (leftMode == 2) {
            // Reverse
            leftMotorSpeed_ = -leftSpeed;
        } else {
            // Off
            leftMotorSpeed_ = 0;
        }

        // Right motor
        if (rightMode == 1) {
            // Forward
            rightMotorSpeed_ = rightSpeed;
        } else if (rightMode == 2) {
            // Reverse
            rightMotorSpeed_ = -rightSpeed;
        } else {
            // Off
            rightMotorSpeed_ = 0;
        }

    }

    void drive_with_heading(uint8_t speed, uint16_t heading, uint8_t flags) {

    }

    void reset_yaw() {
        this->rotation.y = 0;
    }
    threepp::PerspectiveCamera& getVirtualCamera() {
        return virtualCamera;
    }
    void update(float deltaTime) {
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
private:
    threepp::PerspectiveCamera virtualCamera{};
    float leftMotorSpeed_{0.0f};
    float rightMotorSpeed_{0.0f};
    const float maxMotorSpeed_ = 5.0f;
    const float wheelBase_ = 18.0f;

    // Robot state
    float orientation_{0.0f};
    threepp::Vector3 position_{0.0f, 0.0f, 0.0f};


    std::shared_ptr<threepp::Mesh> createMainBody() {
        auto geometry = threepp::BoxGeometry::create(14, 6.5, 18);
        auto material = threepp::MeshBasicMaterial::create();
        material->color = threepp::Color::darkslategray;
        auto mesh = threepp::Mesh::create(geometry, material);
        mesh->position.set(0, 6.5 / 2, 0);  // Set the position of the body
        return mesh;
    }

    static std::shared_ptr<threepp::Mesh> createTrack(float xOffset) {
        auto geometry = threepp::BoxGeometry::create(4, 6, 18);
        auto material = threepp::MeshBasicMaterial::create();
        material->color = threepp::Color::antiquewhite;
        auto mesh = threepp::Mesh::create(geometry, material);
        mesh->position.set(xOffset, 6 / 2, 0);  // Position left track's x-offset
        return mesh;
    }

    static std::shared_ptr<threepp::Mesh> createBelt(float xOffset) {
        auto geometry = threepp::BoxGeometry::create(3.2, 6.3, 18.1);
        auto material = threepp::MeshBasicMaterial::create();
        material->color = threepp::Color::gray;
        auto mesh = threepp::Mesh::create(geometry, material);
        mesh->position.set(xOffset, 6.3 / 2, 0);  // Position right track's x-offset
        return mesh;
    }
};

#endif //SPHEROROBOT_HPP
