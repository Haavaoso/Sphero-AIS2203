//
// Created by havso on 07/10/2024.
//

#ifndef MISC_HPP
#define MISC_HPP
using namespace threepp;

std::shared_ptr<Object3D> createXYZBlock(float length = 5) {
    auto axisGroup = Object3D::create();

    // Create X axis (red)
    auto xGeometry = BoxGeometry::create(length, 0.1f, 0.1f);
    auto xMaterial = MeshBasicMaterial::create();
    xMaterial->color = Color::red;
    auto xAxis = Mesh::create(xGeometry, xMaterial);
    xAxis->position.set(length / 2, 0, 0); // Position at the center of the X axis

    // Create Y axis (green)
    auto yGeometry = BoxGeometry::create(0.1f, length, 0.1f);
    auto yMaterial = MeshBasicMaterial::create();
    yMaterial->color = Color::green;
    auto yAxis = Mesh::create(yGeometry, yMaterial);
    yAxis->position.set(0, length / 2, 0); // Position at the center of the Y axis

    // Create Z axis (blue)
    auto zGeometry = BoxGeometry::create(0.1f, 0.1f, length);
    auto zMaterial = MeshBasicMaterial::create();
    zMaterial->color = Color::blue;
    auto zAxis = Mesh::create(zGeometry, zMaterial);
    zAxis->position.set(0, 0, length / 2); // Position at the center of the Z axis

    // Add axes to the group
    axisGroup->add(xAxis);
    axisGroup->add(yAxis);
    axisGroup->add(zAxis);

    return axisGroup;
}

#endif //MISC_HPP
