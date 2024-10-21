#ifndef SPHEROSIM_IMGUIINTFAC_HPP
#define SPHEROSIM_IMGUIINTFAC_HPP

#include "threepp/threepp.hpp"
#include "threepp/extras/imgui/ImguiContext.hpp"

using namespace threepp;




#include <array>


class MyDriverGui : public ImguiContext {

public:
    explicit MyDriverGui(const threepp::Canvas& canvas);

    void onRender() override;

    void setSensorData(const std::array<float, 3>& data);

    [[nodiscard]] const std::array<float, 3>& getSensorData() const;

private:
    std::array<float, 3> sensorData_;
};

#endif //THREEEEEPPPPSIMULATION_TEXTHANDLES_HPP
