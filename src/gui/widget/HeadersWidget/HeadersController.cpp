#include "gui/widget/HeadersWidget/HeadersController.hpp"

using namespace getit::gui::widget;

void HeadersController::executeBeforeRequest(std::shared_ptr<getit::domain::RequestData> data)
{
    auto headers = getView<HeadersView>()->getHeaders();
    std::map<std::string, std::string>::iterator it;

    for (it = headers.begin(); it != headers.end(); it++) {
        data->addHeader(
            it->first,
            it->second
        );
    }
}