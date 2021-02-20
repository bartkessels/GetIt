#include "gui/widget/HeadersWidget/HeadersController.hpp"

using namespace getit::gui::widget;

HeadersController::HeadersController(std::shared_ptr<IHeadersView> view):
    view(view)
{

}

void HeadersController::executeBeforeRequest(std::shared_ptr<getit::domain::RequestData> data)
{
    for (const auto& [header, value] : view->getHeaders()) {
        data->addHeader(
            header, value
        );
    }
}