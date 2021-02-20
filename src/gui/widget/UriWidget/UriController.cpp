#include "gui/widget/UriWidget/UriController.hpp"

using namespace getit::gui::widget;

UriController::UriController(std::shared_ptr<IUriView> view):
    view(view)
{

}

void UriController::executeBeforeRequest(std::shared_ptr<getit::domain::RequestData> data)
{
    data->setUri(view->getUri());
}