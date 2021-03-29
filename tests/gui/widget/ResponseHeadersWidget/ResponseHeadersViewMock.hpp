#pragma once

#include <map>
#include <string>
#include <trompeloeil.hpp>

#include "gui/widget/ResponseHeadersWidget/IResponseHeadersView.hpp"

class ResponseHeadersViewMock: public getit::gui::widget::IResponseHeadersView
{
    public:
        ~ResponseHeadersViewMock() = default;

        MAKE_MOCK1(setHeaders, void(std::map<std::string, std::string>), override);
};