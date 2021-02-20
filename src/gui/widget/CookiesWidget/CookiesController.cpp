#include "gui/widget/CookiesWidget/CookiesController.hpp"

using namespace getit::gui::widget;

CookiesController::CookiesController(std::shared_ptr<ICookiesView> view):
    view(view)
{

}

void CookiesController::executeBeforeRequest(std::shared_ptr<getit::domain::RequestData> data)
{
    for (const auto& [cookie, value] : view->getCookies()) {
        auto completeCookie = boost::format(cookieHeaderTemplate)
            % cookie % value;

        data->addHeader(
            cookieHeaderName,
            completeCookie.str()
        );
    }
}