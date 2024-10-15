//
// Created by havso on 07/10/2024.
//
//
// Created by havso on 07/10/2024.
//

#include <iostream>
#include "SpheroRobot.hpp"
#include "misc.hpp"

#include <threepp/threepp.hpp>

#include "threepp/helpers/CameraHelper.hpp"
using namespace threepp;

auto createPlane() {
    auto geometry = PlaneGeometry::create(50,50);
    geometry->rotateX(-math::PI/2);
    auto material = MeshBasicMaterial::create();
    material->color = Color::darkgreen;

    return Mesh::create(geometry, material);
}


auto bigObj() {
    auto geometry = BoxGeometry::create(5,5, 30);
    auto material = MeshBasicMaterial::create();
    material->color = Color::black;
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
                robot->translateZ(translationSpeed * deltaTime);
                break;
            }
           case Key::S: {
                robot->translateZ(-translationSpeed * deltaTime);
                break;
            }
            case Key::A: {
                robot->rotateY(translationSpeed * deltaTime);
                break;
            }
            case Key::D: {
                robot->rotateY(-translationSpeed * deltaTime);
                break;
            }
        }
    }
    void onKeyRepeat(KeyEvent evt) override {
        switch (evt.key) {
            case Key::W: {
                robot->translateZ(translationSpeed * deltaTime);
                break;
            }
            case Key::S: {
                robot->translateZ(-translationSpeed * deltaTime);
                break;
            }
            case Key::A: {
                robot->rotateY(translationSpeed * deltaTime);
                break;
            }
            case Key::D: {
                robot->rotateY(-translationSpeed * deltaTime);
                break;
            }
        }
    }
private:
    SpheroRobot *robot;
    float translationSpeed = 50;
    float rotationSpeed = 0.2;

    uint16_t heading = 0;


};

int main() {
    Canvas canvas("SpheroSim");
    GLRenderer renderer(canvas.size());


    Scene scene;
    scene.background = Color::mediumvioletred;

    PerspectiveCamera camera(60, canvas.aspect());
    camera.position.z = 20;
    camera.position.y = 10;


    SpheroRobot robot;
    scene.add(robot);
    auto& virtualCamera = robot.getVirtualCamera();

    auto cameraHelper = CameraHelper::create(virtualCamera);

    scene.add(cameraHelper);
    //cameraHelper->layers.set(1);




    auto plane = createPlane();
    scene.add(plane);

    RobotController keyController(robot);
    OrbitControls controls(camera, canvas);
    Clock clock;
    canvas.addKeyListener(keyController);



    auto obj22 = bigObj();
    obj22->rotateX(math::PI /2);
    obj22->translateX(40);
    scene.add(obj22);
    auto xyzBlock = createXYZBlock();
    xyzBlock->translateX(20);
    scene.add(xyzBlock);




    canvas.onWindowResize([&](WindowSize size) {
        camera.aspect = size.aspect();
        camera.updateProjectionMatrix();
        renderer.setSize(size);
    });

    //std::vector<std::unsigned char> imageData;


    canvas.animate([&] {
        renderer.setScissorTest(false);
        renderer.setViewport(0, 0, canvas.size().width(), canvas.size().height()); // Reset viewport explicitly if needed



        const auto dt = clock.getDelta();
        keyController.deltaTime = dt; // Move this to the start of the loop to ensure consistency

        renderer.clear();

        renderer.render(scene, camera);

        renderer.clearDepth();
        renderer.setScissorTest(true);
        renderer.setScissor(0, 0, 256 * canvas.aspect(), 256);
        renderer.setViewport(0, 0, 256 * canvas.aspect(), 256);
        renderer.render(scene, virtualCamera);

        renderer.setScissorTest(false); // Reset scissor test
        renderer.setViewport(0, 0, canvas.size().width(), canvas.size().height());

        controls.update();



        /*
        const auto dt = clock.getDelta();
        renderer.setSize(canvas.size());

        renderer.clear();

        renderer.render(scene, camera);

        renderer.clearDepth();
        renderer.setViewport(0, 0, 256 * canvas.aspect(), 256);
        renderer.setScissor(0, 0, 256 * canvas.aspect(), 256);
        renderer.setScissorTest(true);
        renderer.render(scene, virtualCamera);
        //renderer.setViewport(0,0,canvas.size().width(), canvas.size().height());
        renderer.setScissor(0,0,canvas.size().width(), canvas.size().height());*/



        //renderer.readPixels({0, 0}, {256 * canvas.aspect(), 256}, Format::BGRA, imageData.data());




    });




    std::cout << "working" << std::endl;

}