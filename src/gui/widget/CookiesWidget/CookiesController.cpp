#include "gui/widget/CookiesWidget/CookiesController.hpp"

using namespace getit::gui::widget;

void CookiesController::executeBeforeRequest(std::shared_ptr<getit::domain::RequestData> data)
{
    auto cookies = getView<CookiesView>()->getCookies();
    std::map<std::string, std::string>::iterator it;

    for (it = cookies.begin(); it != cookies.end(); it++) {
        auto cookie = boost::format(cookieHeaderTemplate)
            % it->first % it->second;

        data->addHeader(
            cookieHeaderName,
            cookie.str()
        );
    }
}