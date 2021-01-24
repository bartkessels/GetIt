#include "gui/widget/UriWidget/UriController.hpp"

using namespace getit::gui::widget;

void UriController::executeBeforeRequest(std::shared_ptr<getit::domain::RequestData> data)
{
    data->setUri(getView<UriView>()->getUri());
}