#include "gui/widget/BodyWidget/RawBodyTab/RawBodyTabController.hpp"

using namespace getit::gui::widget::BodyWidget;

RawBodyTabController::RawBodyTabController(std::shared_ptr<IRawBodyTabView> view):
    view(view)
{

}

void RawBodyTabController::executeBeforeRequest(std::shared_ptr<getit::domain::RequestData> data)
{
    std::string contentType = view->getContentType();
    std::string body = view->getBody();

    auto requestBody = std::make_shared<getit::domain::body::RawRequestBody>(contentType);
    requestBody->setBody(body);

    data->setBody(requestBody);
}