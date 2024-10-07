//
// Created by havso on 07/10/2024.
//
//
// Created by havso on 07/10/2024.
//

#include <iostream>

#include "SpheroRobot.hpp"
#include <threepp/threepp.hpp>
using namespace threepp;

auto createPlane() {
    auto geometry = PlaneGeometry::create(50,50);
    geometry->rotateX(-math::PI/2);
    auto material = MeshBasicMaterial::create();
    material->color = Color::darkgreen;

    return Mesh::create(geometry, material);
}


class RobotController: public KeyListener {
public:

    float deltaTime;

    RobotController(SpheroRobot &robot)
        : robot(&robot) {
    }

    void onKeyPressed(KeyEvent evt) override {
        switch (evt.key) {
            case Key::W: {
                robot->translateZ(translationSpeed* deltaTime);
            }
        }
    }
    void onKeyRepeat(KeyEvent evt) override {
        switch (evt.key) {
            case Key::W: {
                robot->translateZ(translationSpeed* deltaTime);
            }
        }
    }
private:
    SpheroRobot *robot;
    float translationSpeed = 0.1;
    float rotationSpeed = 0.1;

    uint16_t heading = 0;


};

int main() {
    Canvas canvas("SpheroSim");
    GLRenderer renderer(canvas.size());

    Scene scene;
    scene.background = Color::aliceblue;

    PerspectiveCamera camera(60, canvas.aspect());
    camera.position.z = 10;
    SpheroRobot robot;
    scene.add(robot);


    auto plane = createPlane();
    scene.add(plane);

    RobotController keyController(robot);
    OrbitControls controls(camera, canvas);
    Clock clock;

    canvas.animate([&] {
        renderer.render(scene, camera);
        const auto dt = clock.getDelta();
        keyController.deltaTime = dt;


    });

    std::cout << "working" << std::endl;

}