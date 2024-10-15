#ifndef SPHEROROBOT_HPP
#define SPHEROROBOT_HPP

#include <cstdint>
#include "threepp/cameras/PerspectiveCamera.hpp"
#include "threepp/core/Object3D.hpp"
#include "threepp/geometries/BoxGeometry.hpp"
#include "threepp/materials/MeshBasicMaterial.hpp"
#include "threepp/math/MathUtils.hpp"
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
        //virtualCamera.rotateY(threepp::math::PI);
        //virtualCamera.rotateY(threepp::math::PI / 2); // Rotate 90 degrees around Y axis

        Object3D::add(virtualCamera);


    }

    void drive_raw(uint8_t leftMode, uint8_t leftSpeed, uint8_t rightMode, uint8_t rightSpeed) {
        // Implement drive logic here
    }

    void drive_with_heading(uint8_t speed, uint16_t heading, uint8_t flags) {
        // Implement driving with heading logic here
    }

    threepp::PerspectiveCamera& getVirtualCamera() {
        return virtualCamera;
    }

private:
    threepp::PerspectiveCamera virtualCamera{};

    std::shared_ptr<threepp::Mesh> createMainBody() {
        auto geometry = threepp::BoxGeometry::create(14, 6.5, 18);
        auto material = threepp::MeshBasicMaterial::create();
        material->color = threepp::Color::darkslategray;
        auto mesh = threepp::Mesh::create(geometry, material);
        mesh->position.set(0, 6.5 / 2, 0);  // Set the position of the body
        return mesh;
    }

    std::shared_ptr<threepp::Mesh> createTrack(float xOffset) {
        auto geometry = threepp::BoxGeometry::create(4, 6, 18);
        auto material = threepp::MeshBasicMaterial::create();
        material->color = threepp::Color::antiquewhite;
        auto mesh = threepp::Mesh::create(geometry, material);
        mesh->position.set(xOffset, 6 / 2, 0);  // Set position based on the track's x-offset
        return mesh;
    }

    std::shared_ptr<threepp::Mesh> createBelt(float xOffset) {
        auto geometry = threepp::BoxGeometry::create(3.2, 6.3, 18.1);
        auto material = threepp::MeshBasicMaterial::create();
        material->color = threepp::Color::gray;
        auto mesh = threepp::Mesh::create(geometry, material);
        mesh->position.set(xOffset, 6.3 / 2, 0);  // Set position based on the belt's x-offset
        return mesh;
    }
};

#endif //SPHEROROBOT_HPP
