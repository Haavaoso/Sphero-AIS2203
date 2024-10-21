#include <threepp/threepp.hpp>
#include "threepp/extras/imgui/ImguiContext.hpp"
#include "../include/ImguiIntfac.hpp"


MyDriverGui::MyDriverGui(const threepp::Canvas& canvas)
        : ImguiContext(canvas.windowPtr()), sensorData_{0, 0, 0} {

    makeDpiAware();
}



void MyDriverGui::onRender() {
    ImGui::SetNextWindowPos({0, 0}, 0, {0, 0});
    ImGui::SetNextWindowSize({0, 0}, 0);
    ImGui::Begin("Sensor Data Display");


    ImGui::SameLine();
    ImGui::BeginChild("Sensor1Frame", ImVec2(0, 20), true);
    ImGui::Text("Sensor 1 Distance: %.2f", sensorData_[0]);
    ImGui::EndChild();


    ImGui::SameLine();
    ImGui::BeginChild("Sensor2Frame", ImVec2(0, 20), true);
    ImGui::Text("Sensor 2 Distance: %.2f", sensorData_[1]);
    ImGui::EndChild();


    ImGui::SameLine();
    ImGui::BeginChild("Sensor3Frame", ImVec2(0, 20), true);
    ImGui::Text("Sensor 3 Distance: %.2f", sensorData_[2]);
    ImGui::EndChild();

    ImGui::InputFloat3("Sensor Data Override", sensorData_.data());

    ImGui::End();
}

void MyDriverGui::setSensorData(const std::array<float, 3>& data) {
    sensorData_ = data;
}

// Method to retrieve the current sensor data
const std::array<float, 3>& MyDriverGui::getSensorData() const {
    return sensorData_;
}