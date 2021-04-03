#pragma once

#include <string>
#include <trompeloeil.hpp>

#include "gui/widget/ResponseBodyWidget/XmlResponseBodyTab/IXmlResponseBodyTabView.hpp"

class XmlResponseBodyTabViewMock: public getit::gui::widget::ResponseBodyWidget::IXmlResponseBodyTabView
{
    public:
        ~XmlResponseBodyTabViewMock() = default;

        MAKE_MOCK1(setBody, void(std::string), override);
};