#include "gui/widget/ResponseRawBodyWidget/ResponseRawBodyController.hpp"

using namespace getit::gui::widget;

void ResponseRawBodyController::executeAfterRequest(std::shared_ptr<getit::domain::Response> response)
{
    getView<ResponseRawBodyView>()->setBody(response->body);
}