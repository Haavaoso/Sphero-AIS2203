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
    ImGui::BeginChild("Sensor1Frame", ImVec2(80, 70), true);
    ImGui::Text("Sensor \n1 Dist:");
    ImGui::EndChild();


    ImGui::SameLine();
    ImGui::BeginChild("Sensor2Frame", ImVec2(80, 70), true);
    ImGui::Text("Sensor \n2 Dist:");
    ImGui::EndChild();


    ImGui::SameLine();
    ImGui::BeginChild("Sensor3Frame", ImVec2(80, 70), true);
    ImGui::Text("Sensor \n3 Dist:");
    ImGui::EndChild();

//ImGui::AlignTextToFramePadding();
    //ImGui::InputFloat3("", sensorData_.data());
    variableCentering(0.5f);

    ImGui::End();
}
// Inspiration: https://github.com/ocornut/imgui/discussions/3862
// Actually works very well
//can probably make this more reusable for other texts as well
void MyDriverGui::variableCentering(float alignment){
    ImGuiStyle& style = ImGui::GetStyle();

    std::stringstream ss;
    ss << sensorData_[0] << " , " << sensorData_[1] << " , " << sensorData_[2];
    std::string sensorDataStr = ss.str();

    float size = ImGui::CalcTextSize(sensorDataStr.c_str()).x + style.FramePadding.x * 2.0f;
    float avail = ImGui::GetContentRegionAvail().x;

    float off = (avail - size) * alignment;
    if (off > 0.0f)
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

    ImGui::InputFloat3("", sensorData_.data());
}



void MyDriverGui::setSensorData(const std::array<float, 3>& data) {
    sensorData_ = data;
}

// Method to retrieve the current sensor data
const std::array<float, 3>& MyDriverGui::getSensorData() const {
    return sensorData_;
}