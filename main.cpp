
//
// Created by havso on 07/10/2024.
//

#include <iostream>
#include "include/SpheroRobot.hpp"
#include "include/misc.hpp"
#include "include/RobotController.hpp"
#include "include/ObstacleWarnings.hpp"
#include <threepp/threepp.hpp>
#include "include/ImguiIntfac.hpp"
#include "threepp/helpers/CameraHelper.hpp"


using namespace threepp;

auto createPlane() {
    auto geometry = PlaneGeometry::create(500,500);
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



int main() {
    RobotController ctrl;
    Canvas canvas("SpheroSim");
    GLRenderer renderer(canvas.size());


    Scene scene;
    scene.background = Color::mediumvioletred;

    PerspectiveCamera camera(60, canvas.aspect());
    camera.position.z = 20;
    camera.position.y = 10;

    camera.layers.enableAll();


    SpheroRobot robot;
    scene.add(robot);
    auto& virtualCamera = robot.getVirtualCamera();
    auto cameraHelper = CameraHelper::create(virtualCamera);

    scene.add(cameraHelper);
    cameraHelper->layers.set(5);
    //camera->layers.set(1);



    auto plane = createPlane();
    scene.add(plane);

    OrbitControls controls(camera, canvas);
    Clock clock;
    canvas.addKeyListener(ctrl);



    auto obj22 = bigObj();
    obj22->rotateX(math::PI /2);
    obj22->translateX(40);
    scene.add(obj22);
    auto xyzBlock = createXYZBlock();
    xyzBlock->translateX(20);
    scene.add(xyzBlock);

    HUD hud(canvas.size());
    ObstacleWarning warning("HDKAWdjioadokp", 5, 0.7);
    hud.add(warning.getWarningText(), HUD::Options()
            .setNormalizedPosition({1, 1})
            .setHorizontalAlignment(HUD::HorizontalAlignment::RIGHT)
            .setVerticalAlignment(HUD::VerticalAlignment::TOP));




    canvas.onWindowResize([&](WindowSize size) {
        camera.aspect = size.aspect();
        camera.updateProjectionMatrix();
        renderer.setSize(size);

        hud.setSize(size);
    });

    //std::vector<std::unsigned char> imageData;

    MyDriverGui driverGui(canvas);
    driverGui.makeDpiAware();
    std::array<float, 3> constantData = {1.23f, 4.56f, 7.89f};  // Example constant sensor data
    driverGui.setSensorData(constantData);



    canvas.animate([&] {
        const auto dt = clock.getDelta();


        robot.drive_raw(std::get<0>(ctrl.controllerOut()), std::get<1>(ctrl.controllerOut()), std::get<2>(ctrl.controllerOut()), std::get<3>(ctrl.controllerOut()));
        ctrl.update();

        renderer.clear();
        renderer.render(scene, camera);

        robot.update(dt);
        renderer.setScissorTest(false);
        //hud.apply(renderer);


        renderer.setViewport(0, 0, canvas.size().width(), canvas.size().height()); // Reset viewport explicitly if needed
        //hud.apply(renderer);



        //hud.apply(renderer);

        //hud.apply(renderer);

        renderer.clearDepth();

        //hud.apply(renderer);


        renderer.setScissorTest(true);
        renderer.setScissor(0, 0, 256 * canvas.aspect(), 256);
        renderer.setViewport(0, 0, 256 * canvas.aspect(), 256);


        renderer.render(scene, virtualCamera);


        //hud.apply(renderer);


        std::cout << ctrl.getWASD().LEFT_ALT << std::endl;
        renderer.setScissorTest(false); // Reset scissor test
        renderer.setViewport(0, 0, canvas.size().width(),
                             canvas.size().height());


        //hud.apply(renderer);

        controls.update();

        auto& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(canvas.size().width(), canvas.size().height());

        driverGui.render();

        // Optionally render other ImGui elements or handle DPI awareness
        //driverGui.makeDpiAware();  // Adjust UI scaling based on DPI


        //renderer.readPixels({0, 0}, {256 * canvas.aspect(), 256}, Format::BGRA, imageData.data());




    });




    std::cout << "working" << std::endl;

}