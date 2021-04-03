#include "gui/widget/ResponseBodyWidget/JsonResponseBodyTab/JsonResponseBodyTabController.hpp"

using namespace getit::gui::widget::ResponseBodyWidget;

JsonResponseBodyTabController::JsonResponseBodyTabController(std::shared_ptr<IJsonResponseBodyTabView> view):
    view(view)
{

}

void JsonResponseBodyTabController::executeAfterRequest(std::shared_ptr<getit::domain::Response> response)
{
    view->setBody(response->body);
}