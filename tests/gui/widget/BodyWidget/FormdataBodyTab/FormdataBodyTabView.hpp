#pragma once

#include <map>
#include <string>
#include <trompeloeil.hpp>

#include "gui/widget/BodyWidget/FormdataBodyTab/IFormdataBodyTabView.hpp"

class FormdataBodyTabViewMock: public getit::gui::widget::BodyWidget::IFormdataBodyTabView
{
    public:
        ~FormdataBodyTabViewMock() = default;

        MAKE_MOCK0(getElements, (std::map<std::string, std::string>()), override);
        MAKE_MOCK0(getFiles, (std::map<std::string, std::string>()), override);

        MAKE_MOCK1(setElements, void(std::map<std::string, std::string>), override);
        MAKE_MOCK1(setFiles, void(std::map<std::string, std::string>), override);
};