#include "gui/widget/MethodWidget/MethodController.hpp"

using namespace getit::gui::widget;

MethodController::MethodController(std::shared_ptr<IMethodView> view):
    view(view)
{

}

void MethodController::executeBeforeRequest(std::shared_ptr<getit::domain::RequestData> data)
{
    data->setMethod(view->getMethod());
}