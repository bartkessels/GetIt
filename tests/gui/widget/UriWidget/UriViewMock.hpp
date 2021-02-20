#pragma once

#include <string>
#include <trompeloeil.hpp>

#include "gui/widget/UriWidget/IUriView.hpp"

class UriViewMock: public getit::gui::widget::IUriView
{
    public:
        ~UriViewMock() = default;

        MAKE_MOCK0(getUri, std::string(), override);
        MAKE_MOCK1(setUri, void(std::string), override);
};