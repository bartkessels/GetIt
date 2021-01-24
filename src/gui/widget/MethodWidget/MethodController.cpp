#include "gui/widget/MethodWidget/MethodController.hpp"

using namespace getit::gui::widget;

void MethodController::executeBeforeRequest(std::shared_ptr<getit::domain::RequestData> data)
{
    data->setMethod(getView<MethodView>()->getMethod());
}