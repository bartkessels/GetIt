#include "gui/widget/ResponseHeadersWidget/ResponseHeadersController.hpp"

using namespace getit::gui::widget;

ResponseHeadersController::ResponseHeadersController(std::shared_ptr<IResponseHeadersView> view):
    view(view)
{

}

void ResponseHeadersController::executeAfterRequest(std::shared_ptr<getit::domain::Response> response)
{
    this->view->setHeaders(response->headers);
}