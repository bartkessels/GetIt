#include "gui/widget/ResponseHeadersWidget/ResponseHeadersController.hpp"

using namespace getit::gui::widget;

void ResponseHeadersController::executeAfterRequest(std::shared_ptr<getit::domain::Response> response)
{
    getView<ResponseHeadersView>()->setHeaders(response->headers);
}