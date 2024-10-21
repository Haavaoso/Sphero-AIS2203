#ifndef SPHEROROBOT_HPP
#define SPHEROROBOT_HPP

#include <cstdint>
#include <memory>
#include "threepp/cameras/PerspectiveCamera.hpp"
#include "threepp/core/Object3D.hpp"
#include "threepp/geometries/BoxGeometry.hpp"
#include "threepp/materials/MeshBasicMaterial.hpp"
#include "threepp/math/MathUtils.hpp"
#include "threepp/math/Vector3.hpp"
#include "threepp/objects/Mesh.hpp"

class SpheroRobot : public threepp::Object3D {
public:
    SpheroRobot();

    void drive_raw(uint8_t leftMode, uint8_t leftSpeed, uint8_t rightMode, uint8_t rightSpeed);
    void drive_with_heading(uint8_t speed, uint16_t heading, uint8_t flags);
    void reset_yaw();
    threepp::PerspectiveCamera& getVirtualCamera();
    void update(float deltaTime);

private:
    threepp::PerspectiveCamera virtualCamera{};
    float leftMotorSpeed_{0.0f};
    float rightMotorSpeed_{0.0f};
    const float maxMotorSpeed_ = 5.0f;
    const float wheelBase_ = 18.0f;

    // Robot state
    float orientation_{0.0f};
    threepp::Vector3 position_{0.0f, 0.0f, 0.0f};

    std::shared_ptr<threepp::Mesh> createMainBody();
    static std::shared_ptr<threepp::Mesh> createTrack(float xOffset);
    static std::shared_ptr<threepp::Mesh> createBelt(float xOffset);
};

#endif // SPHEROROBOT_HPP