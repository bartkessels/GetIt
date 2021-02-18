#include "gui/widget/RawBodyWidget/RawBodyController.hpp"

using namespace getit::gui::widget;

void RawBodyController::executeBeforeRequest(std::shared_ptr<getit::domain::RequestData> data)
{
    data->setBody(getView<RawBodyView>()->getBody());
}
