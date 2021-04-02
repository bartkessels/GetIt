#pragma once

#include <string>
#include <trompeloeil.hpp>

#include "gui/widget/ResponseBodyWidget/RawResponseBodyTab/IRawResponseBodyTabView.hpp"

class RawResponseBodyTabViewMock: public getit::gui::widget::ResponseBodyWidget::IRawResponseBodyTabView
{
    public:
        ~RawResponseBodyTabViewMock() = default;

        MAKE_MOCK1(setBody, void(std::string), override);
};